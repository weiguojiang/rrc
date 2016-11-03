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

/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <Configuration/configuration_config.h>
#include <Configuration/configuration.h>


#if CONFIGURATION_CONFIG_INCLUDE_UCLI == 1

#include <uCli/ucli.h>
#include <uCli/ucli_argparse.h>
#include <uCli/ucli_handler_macros.h>

static ucli_status_t
configuration_ucli_ucli__minus_f__(ucli_context_t* uc)
{
    char *filename;
    UCLI_COMMAND_INFO(uc,
                      "f", 1,
                      "$group#argv"
                      "$summary#Read the given config file."
                      "$args#<filename>");
    UCLI_ARGPARSE_OR_RETURN(uc, "s", &filename);
    if (ind_cfg_filename_set(filename) < 0) {
        ucli_printf(uc,
                    "Could not set configuration file to %s.  Using defaults\n",
                    filename);
    } else if (ind_cfg_load() < 0) {
        ucli_printf(uc,
                    "Could not load configuration file %s.  Using defaults\n",
                    filename);
    }

    return UCLI_STATUS_OK;
}

static ucli_status_t
configuration_ucli_ucli__config__(ucli_context_t* uc)
{
    char *filename;
    UCLI_COMMAND_INFO(uc,
                      "read", 1,
                      "$summary#Read the given config file."
                      "$args#<filename>");
    UCLI_ARGPARSE_OR_RETURN(uc, "s", &filename);
    if (ind_cfg_filename_set(filename) < 0) {
        ucli_printf(uc,
                    "Could not set configuration file to %s.  Using defaults\n",
                    filename);
    } else if (ind_cfg_load() < 0) {
        ucli_printf(uc,
                    "Could not load configuration file %s.  Using defaults\n",
                    filename);
    }

    return UCLI_STATUS_OK;
}

/* <auto.ucli.handlers.start> */
/******************************************************************************
 *
 * These handler table(s) were autogenerated from the symbols in this
 * source file.
 *
 *****************************************************************************/
static ucli_command_handler_f configuration_ucli_ucli_handlers__[] =
{
    configuration_ucli_ucli__minus_f__,
    configuration_ucli_ucli__config__,
    NULL
};
/******************************************************************************/
/* <auto.ucli.handlers.end> */

static ucli_module_t
configuration_ucli_module__ =
    {
        "configuration_ucli",
        NULL,
        configuration_ucli_ucli_handlers__,
        NULL,
        NULL,
    };

ucli_node_t*
configuration_ucli_node_create(void)
{
    ucli_node_t* n;
    ucli_module_init(&configuration_ucli_module__);
    n = ucli_node_create("configuration", NULL, &configuration_ucli_module__);
    ucli_node_subnode_add(n, ucli_module_log_node_create("configuration"));
    return n;
}

#else
void*
configuration_ucli_node_create(void)
{
    return NULL;
}
#endif

