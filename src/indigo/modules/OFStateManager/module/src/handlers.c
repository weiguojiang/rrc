/****************************************************************
 *
 *        Copyright 2013, Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 ****************************************************************/

/**
 * @file
 * @brief First line of defense against OpenFlow messages
 *
 * See detailed documentation in the Indigo architecture headers.
 */

#include "ofstatemanager_log.h"

#include <OFStateManager/ofstatemanager_config.h>
#include <OFConnectionManager/ofconnectionmanager.h>
#include <indigo/indigo.h>
#include <indigo/of_state_manager.h>
#include <indigo/port_manager.h>
#include <indigo/forwarding.h>
#include <loci/loci.h>
#include <loci/loci_obj_dump.h>
#include "ofstatemanager_decs.h"
#include "ofstatemanager_int.h"
#include "handlers.h"
#include "ft.h"
#include "table.h"
#include "port.h"

static void
flow_mod_err_msg_send(indigo_error_t indigo_err, of_version_t ver,
                      indigo_cxn_id_t cxn_id, of_flow_modify_t *flow_mod);

/****************************************************************
 *
 * Message handling
 *
 ****************************************************************/

/**
 * Function for unhandled message
 */
void
ind_core_unhandled_message(of_object_t *obj, indigo_cxn_id_t cxn_id)
{
    AIM_LOG_WARN("Unhandled message %s from cxn %d.",
                 of_object_id_str[obj->object_id], cxn_id);

    /* Generate error message */
    indigo_cxn_send_error_reply(cxn_id, obj,
                                OF_ERROR_TYPE_BAD_REQUEST,
                                OF_REQUEST_FAILED_BAD_TYPE);
}

/****************************************************************/

/**
 * Handle a packet_out message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 *
 * Note: Ownership of the message is not transferred, so data from obj
 * should be copied.
 */

void
ind_core_packet_out_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_packet_out_t *obj = _obj;

    (void)indigo_fwd_packet_out(obj);
}

/****************************************************************/

/**
 * Handle a port_mod message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_port_mod_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_port_mod_t *obj = _obj;
    indigo_error_t rv;

    rv = indigo_port_modify(obj);
    if (rv != INDIGO_ERROR_NONE) {
        of_version_t ver = obj->version;
        of_port_no_t port_no;

        of_port_mod_port_no_get(obj, &port_no);
        AIM_LOG_ERROR("Failed to modify port %u: %s", port_no, indigo_strerror(rv));

        indigo_cxn_send_error_reply(
                cxn_id, obj,
                OF_ERROR_TYPE_PORT_MOD_FAILED_BY_VERSION(ver),
                OF_PORT_MOD_FAILED_BAD_PORT);
    }
}

/****************************************************************/

/**
 * Handle a port_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_port_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_port_stats_request_t *obj = _obj;
    of_port_stats_reply_t *reply;
    indigo_error_t rv;
    uint32_t xid = 0;

    if (ind_core_ports_registered > 0) {
        reply = of_port_stats_reply_new(obj->version);
        of_port_stats_entry_t *port_stats = of_port_stats_entry_new(reply->version);

        of_port_stats_request_xid_get(obj, &xid);
        of_port_stats_reply_xid_set(reply, xid);

        of_list_port_stats_entry_t entries;
        of_port_stats_reply_entries_bind(reply, &entries);

        of_port_no_t port_no;
        of_port_stats_request_port_no_get(obj, &port_no);
        bool all_ports = port_no == OF_PORT_DEST_WILDCARD;

        struct slot_allocator_iter iter;
        slot_allocator_iter_init(ind_core_port_allocator, &iter);
        uint32_t slot;
        while ((slot = slot_allocator_iter_next(&iter)) != SLOT_INVALID) {
            struct ind_core_port *port = &ind_core_ports[slot];
            if (!all_ports && port->port_no != port_no) {
                continue;
            }
            of_object_truncate(port_stats);
            indigo_error_t rv = indigo_port_stats_get_one(port->port_no, port_stats);
            if (rv) {
                AIM_LOG_ERROR("Failed to get port stats for port %u: %s",
                              port->port_no, indigo_strerror(rv));
            } else if (of_list_port_stats_entry_append(&entries, port_stats) < 0) {
                /* Message full, send current reply and start a new one */
                of_port_stats_reply_flags_set(reply, OF_STATS_REPLY_FLAG_REPLY_MORE);
                indigo_cxn_send_controller_message(cxn_id, reply);

                if ((reply = of_port_stats_reply_new(obj->version)) == NULL) {
                    AIM_DIE("Failed to allocate port_stats reply message");
                }

                of_port_stats_reply_xid_set(reply, xid);
                of_port_stats_reply_entries_bind(reply, &entries);

                if (of_list_port_stats_entry_append(&entries, port_stats) < 0) {
                    AIM_DIE("Unexpectedly failed to append port stats");
                }
            }

            if (!all_ports) {
                break;
            }
        }

        of_port_stats_entry_delete(port_stats);
        indigo_cxn_send_controller_message(cxn_id, reply);
    } else if (indigo_port_stats_get) {
        rv = indigo_port_stats_get(obj, &reply);
        if (rv == INDIGO_ERROR_NONE) {
            /* Set the XID to match the request */
            of_port_stats_request_xid_get(obj, &xid);
            of_port_stats_reply_xid_set(reply, xid);

            indigo_cxn_send_controller_message(cxn_id, reply);
        } else {
            of_port_no_t port_no;
            of_port_stats_request_port_no_get(obj, &port_no);

            AIM_LOG_ERROR("Failed to get stats for port %u: %s",
                          port_no, indigo_strerror(rv));
            /* @todo sending type 0, code 0 error message */
            indigo_cxn_send_error_reply(cxn_id, obj, 0, 0);
        }
    }

}

/****************************************************************/

/**
 * Handle a queue_get_config_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_queue_get_config_request_handler(of_object_t *_obj,
                                          indigo_cxn_id_t cxn_id)
{
    of_queue_get_config_request_t *obj = _obj;
    of_queue_get_config_reply_t *reply;
    indigo_error_t rv;
    uint32_t xid;
    of_port_no_t port;

    of_queue_get_config_request_xid_get(obj, &xid);
    of_queue_get_config_request_port_get(obj, &port);

    rv = indigo_port_queue_config_get(obj, &reply);
    if (rv == INDIGO_ERROR_NONE) {
        of_queue_get_config_reply_xid_set(reply, xid);
        of_queue_get_config_reply_port_set(reply, port);

        indigo_cxn_send_controller_message(cxn_id, reply);
    } else {
        AIM_LOG_ERROR("Failed to get queue config on port %u: %s",
                      port, indigo_strerror(rv));
        /* @todo sending type 0, code 0 error message */
        indigo_cxn_send_error_reply(cxn_id, obj, 0, 0);
    }
}

/****************************************************************/

/**
 * Handle a queue_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_queue_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_queue_stats_request_t *obj = _obj;
    of_queue_stats_reply_t *reply;
    uint32_t xid;
    indigo_error_t rv;

    if (ind_core_ports_registered > 0) {
        reply = of_queue_stats_reply_new(obj->version);
        of_queue_stats_entry_t *queue_stats = of_queue_stats_entry_new(reply->version);

        of_queue_stats_request_xid_get(obj, &xid);
        of_queue_stats_reply_xid_set(reply, xid);

        of_list_queue_stats_entry_t entries;
        of_queue_stats_reply_entries_bind(reply, &entries);

        of_port_no_t port_no;
        of_queue_stats_request_port_no_get(obj, &port_no);
        bool all_ports = port_no == OF_PORT_DEST_WILDCARD;

        uint32_t queue_id;
        of_queue_stats_request_queue_id_get(obj, &queue_id);
        bool all_queues = queue_id == OF_QUEUE_ALL;

        struct slot_allocator_iter iter;
        slot_allocator_iter_init(ind_core_queue_allocator, &iter);
        uint32_t slot;
        while ((slot = slot_allocator_iter_next(&iter)) != SLOT_INVALID) {
            struct ind_core_queue *queue = &ind_core_queues[slot];
            if (!all_ports && queue->port_no != port_no) {
                continue;
            } else if (!all_queues && queue->queue_id != queue_id) {
                continue;
            }
            of_object_truncate(queue_stats);
            indigo_error_t rv = indigo_port_queue_stats_get_one(
                queue->port_no, queue->queue_id, queue_stats);
            if (rv) {
                AIM_LOG_ERROR("Failed to get queue stats for port %u queue %u: %s",
                              queue->port_no, queue->queue_id, indigo_strerror(rv));
            } else if (of_list_queue_stats_entry_append(&entries, queue_stats) < 0) {
                /* Message full, send current reply and start a new one */
                of_queue_stats_reply_flags_set(reply, OF_STATS_REPLY_FLAG_REPLY_MORE);
                indigo_cxn_send_controller_message(cxn_id, reply);

                if ((reply = of_queue_stats_reply_new(obj->version)) == NULL) {
                    AIM_DIE("Failed to allocate queue_stats reply message");
                }

                of_queue_stats_reply_xid_set(reply, xid);
                of_queue_stats_reply_entries_bind(reply, &entries);

                if (of_list_queue_stats_entry_append(&entries, queue_stats) < 0) {
                    AIM_DIE("Unexpectedly failed to append queue stats");
                }
            }
        }

        of_queue_stats_entry_delete(queue_stats);
        indigo_cxn_send_controller_message(cxn_id, reply);
    } else if (indigo_port_queue_stats_get) {
        rv = indigo_port_queue_stats_get(obj, &reply);
        if (rv == INDIGO_ERROR_NONE) {
            /* Set the XID to match the request */
            of_queue_stats_request_xid_get(obj, &xid);
            of_queue_stats_reply_xid_set(reply, xid);

            indigo_cxn_send_controller_message(cxn_id, reply);
        } else {
            of_port_no_t port_no;
            uint32_t queue_id;
            of_queue_stats_request_port_no_get(obj, &port_no);
            of_queue_stats_request_queue_id_get(obj, &queue_id);
            AIM_LOG_ERROR("Failed to get stats for queue %u on port %u: %s",
                        queue_id, port_no, indigo_strerror(rv));
            /* @todo sending type 0, code 0 error message */
            indigo_cxn_send_error_reply(cxn_id, obj, 0, 0);
        }
    }
}

/****************************************************************/

/**
 * Handle a queue_desc_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_queue_desc_request_handler(of_object_t *_obj,
                                    indigo_cxn_id_t cxn_id)
{
    of_queue_desc_stats_request_t *obj = _obj;
    of_queue_desc_stats_reply_t *reply;
    uint32_t xid;
    indigo_error_t rv;

    if (ind_core_ports_registered > 0) {
        reply = of_queue_desc_stats_reply_new(obj->version);
        of_queue_desc_t *queue_desc = of_queue_desc_new(reply->version);

        of_queue_desc_stats_request_xid_get(obj, &xid);
        of_queue_desc_stats_reply_xid_set(reply, xid);

        of_list_queue_desc_t entries;
        of_queue_desc_stats_reply_entries_bind(reply, &entries);

        of_port_no_t port_no;
//        of_queue_desc_stats_request_port_no_get(obj, &port_no);
        bool all_ports = port_no == OF_PORT_DEST_WILDCARD;

        uint32_t queue_id;
 //       of_queue_desc_stats_request_queue_id_get(obj, &queue_id);
        bool all_queues = queue_id == OF_QUEUE_ALL;

        struct slot_allocator_iter iter;
        slot_allocator_iter_init(ind_core_queue_allocator, &iter);
        uint32_t slot;
        while ((slot = slot_allocator_iter_next(&iter)) != SLOT_INVALID) {
            struct ind_core_queue *queue = &ind_core_queues[slot];
            if (!all_ports && queue->port_no != port_no) {
                continue;
            } else if (!all_queues && queue->queue_id != queue_id) {
                continue;
            }
            of_object_truncate(queue_desc);
            rv = indigo_port_queue_desc_get_one(queue->port_no,
                                                queue->queue_id, queue_desc);
            if (rv) {
                AIM_LOG_ERROR("Failed to get queue desc for port %u queue %u: %s",
                              queue->port_no, queue->queue_id, indigo_strerror(rv));
            } else if (of_list_queue_desc_append(&entries, queue_desc) < 0) {
                /* Message full, send current reply and start a new one */
                of_queue_desc_stats_reply_flags_set(reply,
                                                    OF_STATS_REPLY_FLAG_REPLY_MORE);
                indigo_cxn_send_controller_message(cxn_id, reply);

                if ((reply = of_queue_desc_stats_reply_new(obj->version)) == NULL) {
                    AIM_DIE("Failed to allocate queue_desc_stats reply message");
                }

                of_queue_desc_stats_reply_xid_set(reply, xid);
                of_queue_desc_stats_reply_entries_bind(reply, &entries);

                if (of_list_queue_desc_append(&entries, queue_desc) < 0) {
                    AIM_DIE("Unexpectedly failed to append queue desc");
                }
            }
        }

        of_queue_desc_delete(queue_desc);
        indigo_cxn_send_controller_message(cxn_id, reply);
    } else if (indigo_port_queue_desc_get) {
        rv = indigo_port_queue_desc_get(obj, &reply);
        if (rv == INDIGO_ERROR_NONE) {
            /* Set the XID to match the request */
            of_queue_desc_stats_request_xid_get(obj, &xid);
            of_queue_desc_stats_reply_xid_set(reply, xid);

            indigo_cxn_send_controller_message(cxn_id, reply);
        } else {
            of_port_no_t port_no;
            uint32_t queue_id;
  //          of_queue_desc_stats_request_port_no_get(obj, &port_no);
  //          of_queue_desc_stats_request_queue_id_get(obj, &queue_id);
            AIM_LOG_ERROR("Failed to get stats for queue %u on port %u: %s",
                          queue_id, port_no, indigo_strerror(rv));
            /* @todo sending type 0, code 0 error message */
            indigo_cxn_send_error_reply(cxn_id, obj, 0, 0);
        }
    }
}


/****************************************************************/

static indigo_error_t
flow_mod_setup_query(of_flow_modify_t *obj, /* Works with add, mod, del */
                     of_meta_match_t *query,
                     int query_mode,
                     int force_wildcard_port)
{
    INDIGO_MEM_SET(query, 0, sizeof(*query));
    if (obj->version > OF_VERSION_1_0) {
        of_flow_modify_table_id_get(obj, &query->table_id);
    } else {
        query->table_id = TABLE_ID_ANY;
    }
    of_match_t match;
    if (of_flow_modify_match_get(obj, &match) < 0) {
        AIM_LOG_ERROR("Failed to extract match from flow");
        return INDIGO_ERROR_UNKNOWN;
    }
    minimatch_init(&query->minimatch, &match);
    query->mode = query_mode;
    if (query_mode == OF_MATCH_STRICT) {
        query->check_priority = 1;
        of_flow_add_priority_get(obj, &(query->priority));
    }
    if (obj->version >= OF_VERSION_1_1) {
        of_flow_add_cookie_get(obj, &query->cookie);
        of_flow_add_cookie_mask_get(obj, &query->cookie_mask);
    }

    return INDIGO_ERROR_NONE;
}

static indigo_flow_id_t
flow_id_next(void)
{
    static indigo_flow_id_t next_flow_id = 1;

    indigo_flow_id_t result = next_flow_id;

    if (++next_flow_id == 0)  next_flow_id = 1;

    return (result);
}

/**
 * Handle a flow_add message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_flow_add_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    indigo_error_t rv = INDIGO_ERROR_NONE;
    of_flow_modify_t *obj = _obj; /* Coerce to flow_modify object */
    of_meta_match_t query;
    uint16_t flags;
    of_version_t ver;
    uint32_t xid = 0;
    ft_entry_t        *entry = 0;
    indigo_flow_id_t  flow_id;
    uint16_t idle_timeout, hard_timeout;
    minimatch_t minimatch;

    ver = obj->version;

    of_flow_modify_flags_get(obj, &flags);
    of_flow_modify_xid_get(obj, &xid);
    of_flow_modify_idle_timeout_get(obj, &idle_timeout);
    of_flow_modify_hard_timeout_get(obj, &hard_timeout);

    if (flags & OF_FLOW_MOD_FLAG_CHECK_OVERLAP_BY_VERSION(ver)) {
        AIM_LOG_WARN("Flow-mod overlap flag not supported");
        indigo_cxn_send_error_reply(
                cxn_id, obj,
                OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver),
                OF_FLOW_MOD_FAILED_BAD_FLAGS_BY_VERSION(ver));
        return;
    }

    if ((flags & OF_FLOW_MOD_FLAG_EMERG_BY_VERSION(ver)) &&
        (idle_timeout != 0 || hard_timeout != 0)) {
        AIM_LOG_TRACE("Attempted to set timeout on an emergency flow");
        indigo_cxn_send_error_reply(
                cxn_id, obj,
                OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver),
                OF_FLOW_MOD_FAILED_BAD_EMERG_TIMEOUT_BY_VERSION(ver));
        return;
    }

    /* Search table; if match found, replace entry */
    rv = flow_mod_setup_query(obj, &query, OF_MATCH_STRICT, 1);
    if (rv != INDIGO_ERROR_NONE) {
        /* TODO send error */
        return;
    }
    bool strict_match = ft_strict_match(ind_core_ft, &query, &entry) == INDIGO_ERROR_NONE;
    /* We're going to save this minimatch in the flowtable entry */
    minimatch_move(&minimatch, &query.minimatch);
    metamatch_cleanup(&query);

    if (strict_match) {
        if (obj->version == OF_VERSION_1_0) {
            /* Delete existing flow */
            ind_core_flow_entry_delete(entry, INDIGO_FLOW_REMOVED_OVERWRITE, cxn_id);
        } else {
            /* Overwrite existing flow */
            AIM_LOG_TRACE("Overwriting existing flow");
            ind_core_table_t *table = ind_core_table_get(entry->table_id);
            AIM_ASSERT(table != NULL);
            rv = table->ops->entry_modify(table->priv, cxn_id, entry->priv, obj);

            if (rv == INDIGO_ERROR_NONE) {
                ft_overwrite(ind_core_ft, entry, obj);
            } else {
                AIM_LOG_ERROR("Error from Forwarding while modifying flow: %s",
                              indigo_strerror(rv));
                flow_mod_err_msg_send(rv, obj->version, cxn_id, obj);
            }

            minimatch_cleanup(&minimatch);
            return;
        }
    }

    /* No match found, add as normal */
    AIM_LOG_TRACE("Adding new flow");

    flow_id = flow_id_next();

    rv = ft_add(ind_core_ft, flow_id, obj, &minimatch, &entry);
    if (rv != INDIGO_ERROR_NONE) {
        AIM_LOG_INTERNAL("Failed to insert flow in OFStateManager flowtable: %s",
                         indigo_strerror(rv));
        /* TODO send error */
        return;
    }

    ind_core_table_t *table = ind_core_table_get(entry->table_id);
    if (table != NULL) {
        rv = table->ops->entry_create(table->priv, cxn_id,
                                      obj, flow_id, &entry->priv);
    } else {
        rv = INDIGO_ERROR_BAD_TABLE_ID;
    }

    if (rv == INDIGO_ERROR_NONE) {
        AIM_LOG_TRACE("Flow table now has %d entries",
                      ind_core_ft->current_count);
        if (table != NULL) {
            table->num_flows += 1;
        }
    } else { /* Error during insertion at forwarding layer */
       uint32_t xid;

       AIM_LOG_ERROR("Error from Forwarding while inserting flow: %s",
                     indigo_strerror(rv));
       debug_counter_inc(&ft_forwarding_add_error_counter);

       of_flow_add_xid_get(obj, &xid);
       flow_mod_err_msg_send(rv, obj->version, cxn_id,
                             (of_flow_modify_t *)obj);

       /* Free entry in local flow table */
       ft_delete(ind_core_ft, entry);
    }
}

/**
 * Translate the error status into the correct error code for the given
 * OpenFlow version, and send the error message to the controller.
 *
 * WARNING: we only generate 1.0 and 1.3 errors; 
 * 1.1 and 1.2 errors will be mapped to 1.0 errors.
 *
 * @param indigo_err Error status
 * @param ver OpenFlow version
 * @param cxn_id Connection to send to
 * @param flow_mod Request that failed
 */
static void
flow_mod_err_msg_send(indigo_error_t indigo_err, of_version_t ver,
                      indigo_cxn_id_t cxn_id, of_flow_modify_t *flow_mod)
{
    unsigned char errmsgf = 0;
    uint16_t type;
    uint16_t code;
    uint32_t xid;

    of_flow_modify_xid_get(flow_mod, &xid);

    if (ver >= OF_VERSION_1_3) {
        switch (indigo_err) {
        case INDIGO_ERROR_NONE:
            break;

        case INDIGO_ERROR_RESOURCE:  /* fall-through */
        case INDIGO_ERROR_TABLE_FULL:
            type = OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver);
            code = OF_FLOW_MOD_FAILED_TABLE_FULL_BY_VERSION(ver);
            errmsgf = 1;
            break;

        case INDIGO_ERROR_BAD_MATCH:
            type = OF_ERROR_TYPE_BAD_MATCH_BY_VERSION(ver);
            /* @fixme generate proper code instead of hardcoding */
            code = OF_MATCH_FAILED_BAD_TYPE_BY_VERSION(ver);
            errmsgf = 1;
            break;

        case INDIGO_ERROR_BAD_INSTRUCTION:
            type = OF_ERROR_TYPE_BAD_INSTRUCTION_BY_VERSION(ver);
            /* @fixme generate proper code instead of hardcoding */
            code = OF_INSTRUCTION_FAILED_UNKNOWN_INST_BY_VERSION(ver);
            errmsgf = 1;
            break;

        case INDIGO_ERROR_BAD_ACTION:
            type = OF_ERROR_TYPE_BAD_ACTION_BY_VERSION(ver);
            /* @fixme generate proper code instead of hardcoding */
            code = OF_ACTION_FAILED_BAD_TYPE_BY_VERSION(ver);
            errmsgf = 1;
            break;

        case INDIGO_ERROR_BAD_TABLE_ID:
            type = OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver);
            code = OF_FLOW_MOD_FAILED_BAD_TABLE_ID_BY_VERSION(ver);
            errmsgf = 1;
            break;

        case INDIGO_ERROR_NOT_SUPPORTED:  /* fall-through */
        default:
            type = OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver);
            code = OF_FLOW_MOD_FAILED_UNKNOWN_BY_VERSION(ver);
            errmsgf = 1;
        }
    } else {
        /* @fixme only valid for 1.0 */
        type = OF_ERROR_TYPE_FLOW_MOD_FAILED_BY_VERSION(ver);
        switch (indigo_err) {
        case INDIGO_ERROR_NONE:
            break;
 
        case INDIGO_ERROR_RESOURCE:  /* fall-through */
        case INDIGO_ERROR_TABLE_FULL:
            code = OF_FLOW_MOD_FAILED_ALL_TABLES_FULL_BY_VERSION(ver);
            errmsgf = 1;
            break;
 
        case INDIGO_ERROR_NOT_SUPPORTED:    /* fall-through */
        case INDIGO_ERROR_BAD_MATCH:        /* fall-through */
        case INDIGO_ERROR_BAD_INSTRUCTION:  /* fall-through */
        case INDIGO_ERROR_BAD_ACTION:       /* fall-through */
        case INDIGO_ERROR_BAD_TABLE_ID:
            code = OF_FLOW_MOD_FAILED_UNSUPPORTED_BY_VERSION(ver);
            errmsgf = 1;
            break;
 
        default:
            code = OF_FLOW_MOD_FAILED_EPERM_BY_VERSION(ver);
            errmsgf = 1;
        }
    }
 
    if (errmsgf) {
        indigo_cxn_send_error_reply(cxn_id, flow_mod, type, code);
    }
}

/****************************************************************/

/* State for non-strict flow-modify iteration */
struct flow_modify_state {
    of_flow_modify_t *request;
    indigo_cxn_id_t cxn_id;
    int num_matched;
};

/* Flowtable iterator for ind_core_flow_modify_handler */
static void
modify_iter_cb(void *cookie, ft_entry_t *entry)
{
    struct flow_modify_state *state = cookie;

    if (entry != NULL) {
        indigo_error_t rv;
        state->num_matched++;
        ind_core_table_t *table = ind_core_table_get(entry->table_id);
        AIM_ASSERT(table != NULL);
        rv = table->ops->entry_modify(table->priv, state->cxn_id,
                                      entry->priv, state->request);
        if (rv == INDIGO_ERROR_NONE) {
            ft_entry_modify_effects(ind_core_ft, entry, state->request);
        } else {
            AIM_LOG_ERROR("Error from Forwarding while modifying flow: %s",
                          indigo_strerror(rv));
            flow_mod_err_msg_send(rv, state->request->version,
                                  state->cxn_id, state->request);
        }
    } else {
        if (state->num_matched == 0) {
            AIM_LOG_TRACE("No entries to modify, treat as add");
            /* OpenFlow 1.0.0, section 4.6, page 14.  Treat as an add */
            ind_core_flow_add_handler(state->request, state->cxn_id);
        } else {
            AIM_LOG_TRACE("Finished flow modify task");
        }
        indigo_cxn_resume(state->cxn_id);
        of_object_delete(state->request);
        aim_free(state);
    }
}

/**
 * Handle a flow_modify message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_flow_modify_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_flow_modify_t *obj = _obj;
    int rv;
    of_meta_match_t query;

    struct flow_modify_state *state = aim_malloc(sizeof(*state));
    state->request = of_object_dup(obj);
    state->num_matched = 0;
    state->cxn_id = cxn_id;

    rv = flow_mod_setup_query(state->request, &query, OF_MATCH_NON_STRICT, 1);
    if (rv != INDIGO_ERROR_NONE) {
        of_object_delete(state->request);
        aim_free(state);
        return;
    }

    indigo_cxn_pause(cxn_id);

    rv = ft_spawn_iter_task(ind_core_ft, &query, modify_iter_cb, state,
                            IND_SOC_NORMAL_PRIORITY);
    if (rv != INDIGO_ERROR_NONE) {
        indigo_cxn_resume(state->cxn_id);
        of_object_delete(state->request);
        aim_free(state);
        return;
    }
}

/**
 * Handle a flow_modify_strict message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 *
 * Checks that only one entry in local table matches.  See modify_handler
 * above for more info.
 */

void
ind_core_flow_modify_strict_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_flow_modify_strict_t *obj = _obj;
    indigo_error_t rv;
    of_meta_match_t query;
    ft_entry_t *entry;

    /* Form the query */
    rv = flow_mod_setup_query(obj, &query, OF_MATCH_STRICT, 1);
    if (rv != INDIGO_ERROR_NONE) {
        /* TODO send error */
        return;
    }

    rv = ft_strict_match(ind_core_ft, &query, &entry);
    metamatch_cleanup(&query);

    if (rv == INDIGO_ERROR_NOT_FOUND) {
        AIM_LOG_TRACE("No entries to modify strict, treat as add.");
        /* OpenFlow 1.0.0, section 4.6, page 14.  Treat as an add */
        ind_core_flow_add_handler(_obj, cxn_id);
        return;
    }

    ind_core_table_t *table = ind_core_table_get(entry->table_id);
    AIM_ASSERT(table != NULL);

    rv = table->ops->entry_modify(table->priv, cxn_id, entry->priv, obj);

    if (rv == INDIGO_ERROR_NONE) {
        ft_entry_modify_effects(ind_core_ft, entry, obj);
    } else {
        AIM_LOG_ERROR("Error from Forwarding while modifying flow: %s",
                      indigo_strerror(rv));
        flow_mod_err_msg_send(rv, obj->version, cxn_id, obj);
    }
}

/****************************************************************/

/* State for non-strict flow-delete iteration */
struct flow_delete_state {
    indigo_cxn_id_t cxn_id;
};

/* Flowtable iterator for ind_core_flow_delete_handler */
static void
delete_iter_cb(void *cookie, ft_entry_t *entry)
{
    struct flow_delete_state *state = cookie;

    if (entry != NULL) {
        ind_core_flow_entry_delete(entry, INDIGO_FLOW_REMOVED_DELETE, state->cxn_id);
    } else {
        AIM_LOG_TRACE("Finished flow delete task");
        indigo_cxn_resume(state->cxn_id);
        aim_free(state);
    }
}


/**
 * Handle a flow_delete message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_flow_delete_handler(of_object_t *obj, indigo_cxn_id_t cxn_id)
{
    of_meta_match_t query;
    indigo_error_t rv;

    struct flow_delete_state *state = aim_malloc(sizeof(*state));

    rv = flow_mod_setup_query(obj, &query, OF_MATCH_NON_STRICT, 0);
    if (rv != INDIGO_ERROR_NONE) {
        aim_free(state);
        return;
    }

    state->cxn_id = cxn_id;
    indigo_cxn_pause(cxn_id);

    rv = ft_spawn_iter_task(ind_core_ft, &query, delete_iter_cb, state,
                            IND_SOC_NORMAL_PRIORITY);
    if (rv != INDIGO_ERROR_NONE) {
        indigo_cxn_resume(state->cxn_id);
        aim_free(state);
        return;
    }
}

/**
 * Handle a flow_delete_strict message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_flow_delete_strict_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_flow_delete_strict_t *obj = _obj;
    int rv;
    of_meta_match_t query;
    ft_entry_t *entry;

    rv = flow_mod_setup_query((of_flow_modify_t *)obj, &query, OF_MATCH_STRICT, 0);
    if (rv != INDIGO_ERROR_NONE) {
        /* TODO send error */
        return;
    }

    if (ft_strict_match(ind_core_ft, &query, &entry) == INDIGO_ERROR_NONE) {
        ind_core_flow_entry_delete(entry, INDIGO_FLOW_REMOVED_DELETE, cxn_id);
    }

    metamatch_cleanup(&query);
}


/****************************************************************/

/**
 * Handle a get_config_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_get_config_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_get_config_request_t *obj = _obj;
    of_get_config_reply_t *reply = NULL;
    uint32_t xid;

    /* Allocate reply */
    reply = of_get_config_reply_new(obj->version);
    if (reply == NULL) {
        AIM_LOG_TRACE("Could not alloc get_config_reply.");
        return;
    }

    of_get_config_reply_flags_set(reply, ind_core_of_config.flags);
    of_get_config_reply_miss_send_len_set(reply,
         ind_core_of_config.miss_send_len);

    of_get_config_request_xid_get(obj, &xid);
    of_get_config_reply_xid_set(reply, xid);

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/****************************************************************/

struct ind_core_flow_stats_state {
    indigo_cxn_id_t cxn_id;
    of_version_t version;
    uint32_t xid;
    indigo_time_t current_time;
    of_flow_stats_reply_t *reply;
};

static void
ind_core_flow_stats_iter(void *cookie, ft_entry_t *entry)
{
    struct ind_core_flow_stats_state *state = cookie;
    uint32_t secs, nsecs;
    indigo_error_t rv;

    /* Allocate a reply if we don't already have one. */
    if (state->reply == NULL) {
        state->reply = of_flow_stats_reply_new(state->version);
        if (state->reply == NULL) {
            AIM_DIE("Failed to allocate of_flow_stats_reply");
        }

        of_flow_stats_reply_xid_set(state->reply, state->xid);
        of_flow_stats_reply_flags_set(state->reply, 1);
    }

    if (entry == NULL) {
        /* Send last reply */
        of_flow_stats_reply_flags_set(state->reply, 0);
        indigo_cxn_send_controller_message(state->cxn_id, state->reply);

        /* Clean up state */
        indigo_cxn_resume(state->cxn_id);
        aim_free(state);
        return;
    }

    indigo_fi_flow_stats_t flow_stats = {
        .packets = -1,
        .bytes = -1,
    };

    ind_core_table_t *table = ind_core_table_get(entry->table_id);
    AIM_ASSERT(table != NULL);

    rv = table->ops->entry_stats_get(table->priv, state->cxn_id,
                                     entry->priv, &flow_stats);

    if (rv != INDIGO_ERROR_NONE) {
        AIM_LOG_ERROR("Failed to get stats for flow "INDIGO_FLOW_ID_PRINTF_FORMAT": %s",
                      entry->id, indigo_strerror(rv));
        return;
    }

    /* Skip entry if stats request version is not equal to entry version */
    if (state->version != entry->effects.actions->version) {
        AIM_LOG_TRACE("Stats request version (%d) differs from entry version (%d). "
                  "Entry is skipped.",
                  state->version, entry->effects.actions->version);
        return;
    }

    /* TODO use time from flow_stats? */
    calc_duration(state->current_time, entry->insert_time, &secs, &nsecs);

    /* Set up the structures to append an entry to the list */
    {
        of_list_flow_stats_entry_t list;
        of_flow_stats_entry_t stats_entry;
        of_flow_stats_reply_entries_bind(state->reply, &list);
        of_flow_stats_entry_init(&stats_entry, state->reply->version, -1, 1);
        if (of_list_flow_stats_entry_append_bind(&list, &stats_entry)) {
            AIM_LOG_INTERNAL("Failed to append to flow stats list");
            return;
        }

        of_flow_stats_entry_cookie_set(&stats_entry, entry->cookie);
        of_flow_stats_entry_priority_set(&stats_entry, entry->priority);
        of_flow_stats_entry_idle_timeout_set(&stats_entry, entry->idle_timeout);
        of_flow_stats_entry_hard_timeout_set(&stats_entry, entry->hard_timeout);

        if (stats_entry.version >= OF_VERSION_1_3) {
            of_flow_stats_entry_flags_set(&stats_entry, entry->flags);
        }

        of_match_t match;
        minimatch_expand(&entry->minimatch, &match);

        if (of_flow_stats_entry_match_set(&stats_entry, &match)) {
            AIM_LOG_INTERNAL("Failed to set match in flow stats entry");
            return;
        }

        if (stats_entry.version == entry->effects.actions->version) {
            if (stats_entry.version == OF_VERSION_1_0) {
                if (of_flow_stats_entry_actions_set(
                        &stats_entry, entry->effects.actions) < 0) {
                    AIM_LOG_INTERNAL("Failed to set actions list of flow stats entry");
                    return;
                }
            } else {
                if (of_flow_stats_entry_instructions_set(
                        &stats_entry, entry->effects.instructions) < 0) {
                    AIM_LOG_INTERNAL("Failed to set instructions list of flow stats entry");
                    return;
                }
            }
        }

        of_flow_stats_entry_table_id_set(&stats_entry, entry->table_id);
        of_flow_stats_entry_duration_sec_set(&stats_entry, secs);
        of_flow_stats_entry_duration_nsec_set(&stats_entry, nsecs);
        of_flow_stats_entry_packet_count_set(&stats_entry, flow_stats.packets);
        of_flow_stats_entry_byte_count_set(&stats_entry, flow_stats.bytes);
    }

    if (state->reply->length > (1 << 15)) { /* Last object would get too big */
        indigo_cxn_send_controller_message(state->cxn_id, state->reply);
        state->reply = NULL;
    }
}

/**
 * Handle a flow_stats_request message
 * @param _obj Generic type object for the message to be coerced
 * @param cxn_id Connection handler for the owning connection
 * @returns Error code
 */

void
ind_core_flow_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_flow_stats_request_t *obj = _obj;
    of_meta_match_t query;
    struct ind_core_flow_stats_state *state;
    indigo_error_t rv;

    /* Set up the query structure */
    INDIGO_MEM_SET(&query, 0, sizeof(query));
    of_match_t match;
    if (of_flow_stats_request_match_get(obj, &match) < 0) {
        AIM_LOG_INTERNAL("Failed to get flow stats match");
        return;
    }
    minimatch_init(&query.minimatch, &match);
    of_flow_stats_request_table_id_get(obj, &(query.table_id));
    if (obj->version >= OF_VERSION_1_1) {
        of_flow_stats_request_cookie_get(obj, &query.cookie);
        of_flow_stats_request_cookie_mask_get(obj, &query.cookie_mask);
    }

    /* Non strict; do not check priority */
    query.mode = OF_MATCH_NON_STRICT;

    state = aim_malloc(sizeof(*state));
    state->cxn_id = cxn_id;
    state->version = obj->version;
    of_flow_stats_request_xid_get(obj, &state->xid);
    state->current_time = INDIGO_CURRENT_TIME;
    state->reply = NULL;
    indigo_cxn_pause(cxn_id);

    rv = ft_spawn_iter_task(ind_core_ft, &query, ind_core_flow_stats_iter,
                            state, IND_SOC_NORMAL_PRIORITY);
    if (rv != INDIGO_ERROR_NONE) {
        AIM_LOG_INTERNAL("Failed to start flow stats iter: %s", indigo_strerror(rv));
        indigo_cxn_resume(cxn_id);
        aim_free(state);
    }
}

/****************************************************************/

struct ind_core_aggregate_stats_state {
    indigo_cxn_id_t cxn_id;
    of_version_t version;
    uint32_t xid;
    uint64_t packets;
    uint64_t bytes;
    uint32_t flows;
};

static void
ind_core_aggregate_stats_iter(void *cookie, ft_entry_t *entry)
{
    struct ind_core_aggregate_stats_state *state = cookie;
    indigo_error_t rv;

    if (entry != NULL) {
        indigo_fi_flow_stats_t flow_stats = {
            .packets = -1,
            .bytes = -1,
        };

        ind_core_table_t *table = ind_core_table_get(entry->table_id);
        AIM_ASSERT(table != NULL);

        rv = table->ops->entry_stats_get(table->priv, state->cxn_id,
                                         entry->priv, &flow_stats);

        if (rv != INDIGO_ERROR_NONE) {
            AIM_LOG_ERROR("Failed to get stats for flow "INDIGO_FLOW_ID_PRINTF_FORMAT": %s",
                          entry->id, indigo_strerror(rv));
            return;
        }

        state->bytes += flow_stats.bytes;
        state->packets += flow_stats.packets;
        state->flows += 1;
    } else {
        of_aggregate_stats_reply_t* reply;
        reply = of_aggregate_stats_reply_new(state->version);
        if (reply != NULL) {
            of_aggregate_stats_reply_xid_set(reply, state->xid);
            of_aggregate_stats_reply_byte_count_set(reply, state->bytes);
            of_aggregate_stats_reply_packet_count_set(reply, state->packets);
            of_aggregate_stats_reply_flow_count_set(reply, state->flows);
            indigo_cxn_send_controller_message(state->cxn_id, reply);
        } else {
            AIM_DIE("Failed to allocate aggregate stats reply");
        }
        indigo_cxn_resume(state->cxn_id);
        aim_free(state);
    }
}

/**
 * Handle a aggregate_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_aggregate_stats_request_handler(of_object_t *_obj,
                                         indigo_cxn_id_t cxn_id)
{
    of_aggregate_stats_request_t *obj = _obj;
    of_meta_match_t query;
    struct ind_core_aggregate_stats_state *state;
    indigo_error_t rv;

    /* Set up the query structure */
    INDIGO_MEM_SET(&query, 0, sizeof(query));
    of_match_t match;
    if (of_aggregate_stats_request_match_get(obj, &match) < 0) {
        AIM_LOG_INTERNAL("Failed to get aggregate stats match.");
        return;
    }
    minimatch_init(&query.minimatch, &match);
    of_aggregate_stats_request_table_id_get(obj, &(query.table_id));
    if (obj->version >= OF_VERSION_1_1) {
        of_aggregate_stats_request_cookie_get(obj, &query.cookie);
        of_aggregate_stats_request_cookie_mask_get(obj, &query.cookie_mask);
    }

    /* Non strict; do not check priority */
    query.mode = OF_MATCH_NON_STRICT;

    state = aim_malloc(sizeof(*state));
    state->cxn_id = cxn_id;
    state->version = obj->version;
    of_aggregate_stats_request_xid_get(obj, &state->xid);
    state->packets = 0;
    state->bytes = 0;
    state->flows = 0;
    indigo_cxn_pause(cxn_id);

    rv = ft_spawn_iter_task(ind_core_ft, &query, ind_core_aggregate_stats_iter,
                            state, IND_SOC_NORMAL_PRIORITY);
    if (rv != INDIGO_ERROR_NONE) {
        AIM_LOG_INTERNAL("Failed to start aggregate stats iter: %s", indigo_strerror(rv));
        indigo_cxn_resume(cxn_id);
        aim_free(state);
        return;
    }
}

/****************************************************************/

/**
 * Handle a desc_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_desc_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_desc_stats_request_t *obj = _obj;
    of_desc_stats_reply_t *reply;
    uint32_t xid;
    ind_core_desc_stats_t *data;

    /* Create reply and send to controller */
    if ((reply = of_desc_stats_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate desc stats reply message");
    }

    of_desc_stats_request_xid_get(obj, &xid);
    of_desc_stats_reply_xid_set(reply, xid);

    data = &ind_core_of_config.desc_stats;
    of_desc_stats_reply_sw_desc_set(reply, data->sw_desc);
    of_desc_stats_reply_hw_desc_set(reply, data->hw_desc);
    of_desc_stats_reply_dp_desc_set(reply, data->dp_desc);
    of_desc_stats_reply_mfr_desc_set(reply, data->mfr_desc);
    of_desc_stats_reply_serial_num_set(reply, data->serial_num);
    of_desc_stats_reply_flags_set(reply, 0);

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/****************************************************************/

/**
 * Handle a table_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_table_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_table_stats_request_t *obj = _obj;
    of_table_stats_request_t *reply = NULL;
    of_version_t version = obj->version;

    reply = of_table_stats_reply_new(version);
    AIM_TRUE_OR_DIE(reply != NULL);

    uint32_t xid;
    of_table_stats_request_xid_get(obj, &xid);
    of_table_stats_reply_xid_set(reply, xid);

    of_list_table_stats_entry_t list[1];
    of_table_stats_reply_entries_bind(reply, list);

    int i;
    for (i = 0; i < 256; i++) {
        ind_core_table_t *table = ind_core_table_get(i);

        if (table == NULL) {
            continue;
        }

        indigo_fi_table_stats_t table_stats;
        memset(&table_stats, -1, sizeof(table_stats));

        if (table->ops->table_stats_get) {
            (void) table->ops->table_stats_get(table->priv, cxn_id, &table_stats);
        }

        of_table_stats_entry_t entry[1];
        of_table_stats_entry_init(entry, version, -1, 1);
        (void) of_list_table_stats_entry_append_bind(list, entry);

        of_table_stats_entry_table_id_set(entry, i);
        if (version < OF_VERSION_1_3) {
            of_table_stats_entry_name_set(entry, table->name);
            of_table_stats_entry_max_entries_set(entry, table_stats.max_entries);
        }
        if (version < OF_VERSION_1_2) {
            of_table_stats_entry_wildcards_set(entry, 0x3fffff); /* All wildcards */
        }
        of_table_stats_entry_active_count_set(entry, table->num_flows);
        of_table_stats_entry_lookup_count_set(entry, table_stats.lookup_count);
        of_table_stats_entry_matched_count_set(entry, table_stats.matched_count);
    }

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/****************************************************************/

/**
 * Handle a port_desc_stats_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_port_desc_stats_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    uint32_t xid;
    of_port_desc_stats_request_t *obj = _obj;
    of_port_desc_stats_reply_t *reply;

    /* Generate a port_desc_stats reply and send to controller */
    if ((reply = of_port_desc_stats_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate port_desc_stats reply message");
    }

    of_port_desc_stats_request_xid_get(obj, &xid);
    of_port_desc_stats_reply_xid_set(reply, xid);

    if (ind_core_ports_registered > 0) {
        of_port_desc_t *port_desc = of_port_desc_new(reply->version);

        of_list_port_desc_t entries;
        of_port_desc_stats_reply_entries_bind(reply, &entries);

        struct slot_allocator_iter iter;
        slot_allocator_iter_init(ind_core_port_allocator, &iter);
        uint32_t slot;
        while ((slot = slot_allocator_iter_next(&iter)) != SLOT_INVALID) {
            struct ind_core_port *port = &ind_core_ports[slot];
            of_object_truncate(port_desc);
            indigo_error_t rv = indigo_port_desc_stats_get_one(port->port_no, port_desc);
            if (rv) {
                AIM_LOG_ERROR("Failed to get port desc stats for port %u: %s",
                              port->port_no, indigo_strerror(rv));
            } else if (of_list_port_desc_append(&entries, port_desc) < 0) {
                /* Message full, send current reply and start a new one */
                of_port_desc_stats_reply_flags_set(reply, OF_STATS_REPLY_FLAG_REPLY_MORE);
                indigo_cxn_send_controller_message(cxn_id, reply);

                if ((reply = of_port_desc_stats_reply_new(obj->version)) == NULL) {
                    AIM_DIE("Failed to allocate port_desc_stats reply message");
                }

                of_port_desc_stats_reply_xid_set(reply, xid);
                of_port_desc_stats_reply_entries_bind(reply, &entries);

                if (of_list_port_desc_append(&entries, port_desc) < 0) {
                    AIM_DIE("Unexpectedly failed to append port desc stats");
                }
            }
        }
        of_port_desc_delete(port_desc);
    } else if (indigo_port_desc_stats_get) {
        indigo_port_desc_stats_get(reply);
    }

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/****************************************************************/

/**
 * Handle a features_request message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_features_request_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_features_request_t *obj = _obj;
    of_features_reply_t *reply;
    uint32_t xid;
    of_dpid_t dpid;
    indigo_error_t rv;

    /* Generate a features reply and send to controller */
    if ((reply = of_features_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate features reply message");
    }

    of_features_request_xid_get(obj, &xid);
    of_features_reply_xid_set(reply, xid);
    indigo_core_dpid_get(&dpid);
    of_features_reply_datapath_id_set(reply, dpid);
    of_features_reply_n_buffers_set(reply, 0);

    if ((rv = indigo_fwd_forwarding_features_get(reply)) < 0) {
        AIM_LOG_INTERNAL("Failed to get Forwarding features: %s", indigo_strerror(rv));
    }

    if ((rv = indigo_port_features_get(reply)) < 0) {
        AIM_LOG_INTERNAL("Failed to get PortManager features: %s", indigo_strerror(rv));
    }

    if (obj->version >= OF_VERSION_1_3) {
        uint8_t auxiliary_id;
        indigo_cxn_get_auxiliary_id(cxn_id, &auxiliary_id);
        of_features_reply_auxiliary_id_set(reply, auxiliary_id);
    }

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/**
 * Handle a set_config message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_set_config_handler(of_object_t *_obj, indigo_cxn_id_t cxn_id)
{
    of_set_config_t *obj = _obj;

    /* Handle object of type of_set_config_t */
    ind_core_of_config.config_set_done = 1;
    of_set_config_flags_get(obj, &ind_core_of_config.flags);
    AIM_LOG_VERBOSE("Config flags set to 0x%x", ind_core_of_config.flags);
    of_set_config_miss_send_len_get(obj, &ind_core_of_config.miss_send_len);
    AIM_LOG_VERBOSE("Miss send len set to %d", ind_core_of_config.miss_send_len);
}

/**
 * Handle an experimenter message
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 *
 * The state manager has no specific support for experimenter messages.
 * However, the port or forwarding modules may have that support
 * independent of the state manager.  For this reason, the state
 * manager calls both the port manager and forwarding modules with
 * the request.
 *
 * Currently there is no support for asynchronous experimenter message
 * handling at this layer (so barriers currently will not track experimenter
 * messages correctly).
 *
 * The port and forwarding modules must respond as follows:
 *    INDIGO_ERROR_NONE:  Supported request, no error.
 *    INDIGO_ERROR_NOT_SUPPORTED:  Module does not support the request
 *    INDIGO_ERROR_xxx: Supported request, but error occurred.
 *
 * If both modules respond with NOT_SUPPORTED, then an unknown message
 * type error is generated and sent back to the controller connection.
 *
 * If either module responds with NONE, the operation is considered
 * successful.
 *
 * Otherwise, if either module responds with an error other than
 * supported, behavior is TBD.
 *
 */

void
ind_core_experimenter_handler(of_object_t *obj, indigo_cxn_id_t cxn_id)
{
    indigo_error_t fwd_rv;
    indigo_error_t port_rv;
    indigo_error_t rv = INDIGO_ERROR_NONE;

    /* Handle object of type of_experimenter_t */
    if ((fwd_rv = indigo_fwd_experimenter(obj, cxn_id)) < 0) {
        AIM_LOG_TRACE("Error from fwd_experimenter: %s", indigo_strerror(fwd_rv));
    }
    if ((port_rv = indigo_port_experimenter(obj, cxn_id)) < 0) {
        AIM_LOG_TRACE("Error from port_experimenter: %s", indigo_strerror(port_rv));
    }

    if ((fwd_rv == INDIGO_ERROR_NOT_SUPPORTED) &&
        (port_rv == INDIGO_ERROR_NOT_SUPPORTED)) {
        indigo_cxn_send_error_reply(
                cxn_id, obj,
                OF_ERROR_TYPE_BAD_REQUEST,
                OF_REQUEST_FAILED_BAD_EXPERIMENTER);
    } else if ((fwd_rv != INDIGO_ERROR_NONE) &&
               (port_rv != INDIGO_ERROR_NONE)) {
        /* Not handled and some error */
        if (port_rv != INDIGO_ERROR_NONE) {
            rv = port_rv;
        }
        if (fwd_rv != INDIGO_ERROR_NONE) {
            rv = fwd_rv;
        }
    }

    if (rv < 0) {
        AIM_LOG_VERBOSE("Error handling experimenter message in port or fwding");
    }
}

/****************************************************************
 *
 * Extension message handling
 *
 ****************************************************************/

/**
 * Handle a BSN hybrid get request
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_bsn_hybrid_get_request_handler(of_object_t *_obj,
                                        indigo_cxn_id_t cxn_id)
{
    of_bsn_hybrid_get_request_t *obj = _obj;
    of_bsn_hybrid_get_reply_t *reply;
    uint32_t xid;

    AIM_LOG_TRACE("Received BSN hybrid_get message from %d", cxn_id);

    /* Create reply and send to controller */
    if ((reply = of_bsn_hybrid_get_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate hybrid_get reply message");
    }

    of_bsn_hybrid_get_request_xid_get(obj, &xid);
    of_bsn_hybrid_get_reply_xid_set(reply, xid);
    of_bsn_hybrid_get_reply_hybrid_enable_set(reply, 1);
    of_bsn_hybrid_get_reply_hybrid_version_set(reply, 0);

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/**
 * Handle a BSN switch pipeline get request
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_bsn_sw_pipeline_get_request_handler(of_object_t *_obj,
                                             indigo_cxn_id_t cxn_id)
{
    of_bsn_get_switch_pipeline_request_t *obj = _obj;
    of_bsn_get_switch_pipeline_reply_t *reply;
    uint32_t xid;
    of_desc_str_t pipeline;

    if ((reply = of_bsn_get_switch_pipeline_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate sw pipeline get reply message");
    }

    of_bsn_get_switch_pipeline_request_xid_get(obj, &xid);

    indigo_fwd_pipeline_get(pipeline);

    of_bsn_get_switch_pipeline_reply_xid_set(reply, xid);
    of_bsn_get_switch_pipeline_reply_pipeline_set(reply, pipeline);

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/**
 * Handle a BSN switch pipeline set request
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_bsn_sw_pipeline_set_request_handler(of_object_t *_obj,
                                             indigo_cxn_id_t cxn_id)
{
    of_bsn_set_switch_pipeline_request_t *obj = _obj;
    of_bsn_set_switch_pipeline_reply_t *reply;
    uint32_t xid;
    int rv;
    of_desc_str_t pipeline;

    if ((reply = of_bsn_set_switch_pipeline_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate sw pipeline set reply message");
    }

    of_bsn_set_switch_pipeline_request_pipeline_get(obj, &pipeline);
    of_bsn_set_switch_pipeline_request_xid_get(obj, &xid);

    AIM_LOG_VERBOSE("Setting pipeline: %s", pipeline);
    if ((rv = indigo_fwd_pipeline_set(pipeline)) != INDIGO_ERROR_NONE) {
        AIM_LOG_ERROR("Failed to set switch pipeline: %s", indigo_strerror(rv));
        of_bsn_set_switch_pipeline_reply_status_set(reply, 1);
    } else {
        of_bsn_set_switch_pipeline_reply_status_set(reply, 0);
    }

    of_bsn_set_switch_pipeline_reply_xid_set(reply, xid);

    indigo_cxn_send_controller_message(cxn_id, reply);
}

/**
 * Handle a BSN switch pipeline stats request
 * @param cxn_id Connection handler for the owning connection
 * @param _obj Generic type object for the message to be coerced
 * @returns Error code
 */

void
ind_core_bsn_sw_pipeline_stats_request_handler(of_object_t *_obj,
                                               indigo_cxn_id_t cxn_id)
{
    of_bsn_switch_pipeline_stats_request_t *obj = _obj;
    of_bsn_switch_pipeline_stats_reply_t *reply;
    of_version_t version;
    uint32_t xid;
    int i;
    int num_pipelines;
    of_desc_str_t *pipelines;

    if ((reply = of_bsn_switch_pipeline_stats_reply_new(obj->version)) == NULL) {
        AIM_DIE("Failed to allocate sw pipeline stats reply message");
    }

    version = obj->version;
    of_bsn_switch_pipeline_stats_request_xid_get(obj, &xid);
    of_bsn_switch_pipeline_stats_reply_xid_set(reply, xid);

    indigo_fwd_pipeline_stats_get(&pipelines, &num_pipelines);
    of_list_bsn_switch_pipeline_stats_entry_t list;
    of_bsn_switch_pipeline_stats_reply_entries_bind(reply, &list);
    for (i = 0; i < num_pipelines; i++) {
        of_bsn_switch_pipeline_stats_entry_t entry;

        of_bsn_switch_pipeline_stats_entry_init(&entry, version, -1, 1);
        if (of_list_bsn_switch_pipeline_stats_entry_append_bind(&list,
                                                                &entry)) {
            AIM_LOG_INTERNAL("Failed to append to pipeline stats list");
            break;
        } else {
            of_bsn_switch_pipeline_stats_entry_pipeline_set(&entry,
                                                            pipelines[i]);
        }
    }
    aim_free(pipelines);

    indigo_cxn_send_controller_message(cxn_id, reply);
}
