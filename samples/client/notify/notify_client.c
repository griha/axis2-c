/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <axiom.h>
#include <axis2_util.h>
#include <axiom_soap.h>
#include <axis2_client.h>

axiom_node_t *
build_om_programatically(const axis2_env_t *env);

int main(int argc, char** argv)
{
    const axis2_env_t *env = NULL;
    const axis2_char_t *address = NULL;
    axis2_endpoint_ref_t* endpoint_ref = NULL;
    axis2_options_t *options = NULL;
    const axis2_char_t *client_home = NULL;
    axis2_svc_client_t* svc_client = NULL;
    axiom_node_t *payload = NULL;
    axis2_status_t status = AXIS2_FAILURE;

    /* Set up the environment */
    env = axis2_env_create_all("notify.log", AXIS2_LOG_LEVEL_TRACE);

    /* Set end point reference of echo service */
    address = "http://localhost:9090/axis2/services/notify";
    if (argc > 1)
        address = argv[1];
    if (AXIS2_STRCMP(address, "-h") == 0)
    {
        printf("Usage : %s [endpoint_url]\n", argv[0]);
        printf("use -h for help\n");
        return 0;
    }
    printf("Using endpoint : %s\n", address);

    /* Create EPR with given address */
    endpoint_ref = axis2_endpoint_ref_create(env, address);

    /* Setup options */
    options = axis2_options_create(env);
    AXIS2_OPTIONS_SET_TO(options, env, endpoint_ref);
    AXIS2_OPTIONS_SET_ACTION(options, env,
            "http://example.org/action/notify");

    /* Set up deploy folder. It is from the deploy folder, the configuration is picked up
     * using the axis2.xml file.
     * In this sample client_home points to the Axis2/C default deploy folder. The client_home can 
     * be different from this folder on your system. For example, you may have a different folder 
     * (say, my_client_folder) with its own axis2.xml file. my_client_folder/modules will have the 
     * modules that the client uses
     */
    client_home = AXIS2_GETENV("AXIS2C_HOME");
    if (!client_home)
        client_home = "../../deploy";

    /* Create service client */
    svc_client = axis2_svc_client_create(env, client_home);
    if (!svc_client)
    {
        printf("Error creating service client\n");
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Stub invoke FAILED: Error code:"
                " %d :: %s", env->error->error_number,
                AXIS2_ERROR_GET_MESSAGE(env->error));
    }

    /* Set service client options */
    AXIS2_SVC_CLIENT_SET_OPTIONS(svc_client, env, options);

    /* Engage addressing module */
    /*AXIS2_SVC_CLIENT_ENGAGE_MODULE(svc_client, env, AXIS2_MODULE_ADDRESSING);*/

    /* Build the SOAP request message payload using OM API.*/
    payload = build_om_programatically(env);

    /* Send request */
    status = AXIS2_SVC_CLIENT_SEND_ROBUST(svc_client, env, payload);

    if (status == AXIS2_SUCCESS)
    {
        printf("\nnotify client invoke SUCCESSFUL!\n");
    }
    else
    {
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Stub invoke FAILED: Error code:"
                " %d :: %s", env->error->error_number,
                AXIS2_ERROR_GET_MESSAGE(env->error));
        printf("notify client invoke FAILED!\n");
    }

    payload = build_om_programatically(env);
    /* Send request */
    status = AXIS2_SVC_CLIENT_SEND_ROBUST(svc_client, env, payload);
    if (status == AXIS2_SUCCESS)
    {
        printf("\nnotify client invoke SUCCESSFUL!\n");
    }
    else
    {
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI, "Stub invoke FAILED: Error code:"
                " %d :: %s", env->error->error_number,
                AXIS2_ERROR_GET_MESSAGE(env->error));
        printf("notify client invoke FAILED!\n");
    }

    if (svc_client)
    {
        AXIS2_SVC_CLIENT_FREE(svc_client, env);
        svc_client = NULL;
    }
    return 0;
}

/* build SOAP request message content using OM */
axiom_node_t *
build_om_programatically(const axis2_env_t *env)
{
    axiom_node_t *notify_om_node = NULL;
    axiom_element_t* notify_om_ele = NULL;
    axiom_namespace_t *ns1 = NULL;
    axis2_char_t *buffer = NULL;

    ns1 = axiom_namespace_create(env, "http://example.org/notify", "m");
    notify_om_ele = axiom_element_create(env, NULL, "notify", ns1, &notify_om_node);
    AXIOM_ELEMENT_SET_TEXT(notify_om_ele, env, "notify5", notify_om_node);

    buffer = AXIOM_NODE_TO_STRING(notify_om_node, env);
    printf("\nSending OM node in XML : %s \n",  buffer);

    return notify_om_node;
}
