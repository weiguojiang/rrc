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
 ***************************************************************/
/************************************************************//**
 *
 * VPI Generic uCli Interfaces.
 *
 * Available for Query, Status, and Debug.
 *
 ***************************************************************/
#include <VPI/vpi_config.h>

#if VPI_CONFIG_INCLUDE_UCLI == 1

#include <VPI/vpi.h>
#include <uCli/ucli.h>
#include <uCli/ucli_argparse.h>
#include <uCli/ucli_handler_macros.h>
#include "vpi_int.h"

static ucli_status_t
vpi_ucli_ucli__config__(ucli_context_t* uc)
{
    UCLI_HANDLER_MACRO_MODULE_CONFIG(vpi);
    return 0;
}

static ucli_status_t
vpi_ucli_ucli__list__(ucli_context_t* uc)
{
    /* fixme - locked */
    UCLI_HANDLER_MACRO_MODULE_LIST(vpi, vpi_t, vpi, vpi_instances__->list);
}

static ucli_status_t
vpi_ucli_ucli__show__(ucli_context_t* uc)
{
    /* fixme - locked */
    UCLI_HANDLER_MACRO_MODULE_SHOW(vpi, vpi_t, vpi, vpi_instances__->list);
}

/* <auto.ucli.handlers.start> */
/******************************************************************************
 *
 * These handler table(s) were autogenerated from the symbols in this
 * source file.
 *
 *****************************************************************************/
static ucli_command_handler_f vpi_ucli_ucli_handlers__[] =
{
    vpi_ucli_ucli__config__,
    vpi_ucli_ucli__list__,
    vpi_ucli_ucli__show__,
    NULL
};
/******************************************************************************/
/* <auto.ucli.handlers.end> */


static ucli_module_t
vpi_ucli_module__ =
    {
        "vpi_ucli",
        NULL,
        vpi_ucli_ucli_handlers__,
        NULL,
        NULL,
    };


ucli_node_t*
vpi_ucli_node_create(void)
{
    ucli_node_t* n;
    ucli_module_init(&vpi_ucli_module__);
    n = ucli_node_create("vpi", NULL, &vpi_ucli_module__);
    ucli_node_subnode_add(n, ucli_module_log_node_create("vpi"));
    return n;
}

#else
void*
vpi_ucli_node_create(void)
{
    return NULL;
}
#endif



