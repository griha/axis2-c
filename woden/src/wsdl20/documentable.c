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

#include <woden/wsdl20/axis2_woden_documentable.h>
#include <woden/wsdl20/xml/axis2_woden_documentation_element.h>

typedef struct axis2_woden_documentable_impl axis2_woden_documentable_impl_t;

/** 
 * @brief Documentable Struct Impl
 *	Axis2 Documentable  
 */ 
struct axis2_woden_documentable_impl
{
    axis2_woden_documentable_t documentable;
    axis2_woden_wsdl_obj_t *wsdl_obj;
    axis2_hash_t *super;
    axis2_array_list_t *f_doc_elems;
};

#define INTF_TO_IMPL(documentable) ((axis2_woden_documentable_impl_t *) documentable)

axis2_status_t AXIS2_CALL 
axis2_woden_documentable_free(
        void *documentable,
        const axis2_env_t *env);

axis2_hash_t *AXIS2_CALL 
axis2_woden_documentable_super_objs(
        void *documentable,
        const axis2_env_t *env);

axis2_woden_wsdl_obj_t *AXIS2_CALL
axis2_woden_documentable_get_base_impl(
        void *documentable,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_woden_documentable_add_documentation_element(
        void *documentable,
        const axis2_env_t *env,
        axis2_woden_documentation_element_t *documentation);

axis2_array_list_t *AXIS2_CALL
axis2_woden_documentable_get_documentation_elements(
        void *documentable,
        const axis2_env_t *env);

static axis2_woden_documentable_t *
create(
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;
   
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    documentable_impl = AXIS2_MALLOC(env->allocator, 
                    sizeof(axis2_woden_documentable_impl_t));

    documentable_impl->f_doc_elems = NULL;
    documentable_impl->super = NULL;
    
    documentable_impl->documentable.ops = AXIS2_MALLOC(env->allocator, 
                    sizeof(axis2_woden_documentable_ops_t));

    documentable_impl->documentable.ops->free = axis2_woden_documentable_free;
    documentable_impl->documentable.ops->super_objs = axis2_woden_documentable_super_objs;
    documentable_impl->documentable.ops->get_base_impl = axis2_woden_documentable_get_base_impl;
    documentable_impl->documentable.ops->add_documentation_element = 
        axis2_woden_documentable_add_documentation_element;
    documentable_impl->documentable.ops->get_documentation_elements = 
        axis2_woden_documentable_get_documentation_elements;

    return &(documentable_impl->documentable);
}

AXIS2_EXTERN axis2_woden_documentable_t * AXIS2_CALL
axis2_woden_documentable_create(
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;
   
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    documentable_impl = (axis2_woden_documentable_impl_t *) create(env);

    documentable_impl->wsdl_obj = axis2_woden_wsdl_obj_create(env);

    documentable_impl->super = axis2_hash_make(env);
    if(!documentable_impl->super)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(documentable_impl->super, "AXIS2_WODEN_DOCUMENTABLE", 
            AXIS2_HASH_KEY_STRING, &(documentable_impl->documentable));
    axis2_hash_set(documentable_impl->super, "AXIS2_WODEN_WSDL_OBJ", 
            AXIS2_HASH_KEY_STRING, documentable_impl->wsdl_obj);
            

    return &(documentable_impl->documentable);
}

axis2_status_t AXIS2_CALL
axis2_woden_documentable_free(
        void *documentable,
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    documentable_impl = INTF_TO_IMPL(documentable);

    if(documentable_impl->f_doc_elems)
    {
        AXIS2_ARRAY_LIST_FREE(documentable_impl->f_doc_elems, env);
        documentable_impl->f_doc_elems = NULL;
    }
    
    if(documentable_impl->wsdl_obj)
    {
        AXIS2_WODEN_WSDL_OBJ_FREE(documentable_impl->wsdl_obj, env);
        documentable_impl->wsdl_obj = NULL;
    }

    if(documentable_impl->super)
    {
        axis2_hash_free(documentable_impl->super, env);
        documentable_impl->super = NULL;
    }
    
    if(documentable_impl->documentable.ops)
    {
        AXIS2_FREE(env->allocator, documentable_impl->documentable.ops);
        documentable_impl->documentable.ops = NULL;
    }
    
    if(documentable_impl)
    {
        AXIS2_FREE(env->allocator, documentable_impl);
        documentable_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

axis2_hash_t *AXIS2_CALL
axis2_woden_documentable_super_objs(
        void *documentable,
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    documentable_impl = INTF_TO_IMPL(documentable);

    return documentable_impl->super;
}

axis2_woden_wsdl_obj_t *AXIS2_CALL
axis2_woden_documentable_get_base_impl(
        void *documentable,
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    documentable_impl = INTF_TO_IMPL(documentable);

    return documentable_impl->wsdl_obj;
}

axis2_status_t AXIS2_CALL
axis2_woden_documentable_resolve_methods(
        axis2_woden_documentable_t *documentable,
        const axis2_env_t *env,
        axis2_woden_documentable_t *documentable_impl,
        axis2_hash_t *methods)
{
    axis2_woden_documentable_impl_t *documentable_impl_l = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, methods, AXIS2_FAILURE);
    documentable_impl_l = INTF_TO_IMPL(documentable_impl);

    documentable->ops = AXIS2_MALLOC(env->allocator, 
                sizeof(axis2_woden_documentable_ops_t));
    
    documentable->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    documentable->ops->to_documentable_free = axis2_hash_get(methods, 
            "to_documentable_free", AXIS2_HASH_KEY_STRING);
    documentable->ops->super_objs = axis2_hash_get(methods, "super_objs", 
            AXIS2_HASH_KEY_STRING);

    documentable->ops->add_documentation_element = axis2_hash_get(methods, 
            "add_documentation_element", AXIS2_HASH_KEY_STRING);
    if(!documentable->ops->add_documentation_element && documentable_impl_l)
            documentable->ops->add_documentation_element = 
            documentable_impl_l->documentable.ops->add_documentation_element;

    documentable->ops->get_documentation_elements = axis2_hash_get(methods, 
            "get_documentation_elements", AXIS2_HASH_KEY_STRING);
    if(!documentable->ops->get_documentation_elements && documentable_impl_l)
            documentable->ops->get_documentation_elements = 
            documentable_impl_l->documentable.ops->get_documentation_elements;
    
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_woden_documentable_add_documentation_element(
        void *documentable,
        const axis2_env_t *env,
        axis2_woden_documentation_element_t *documentation)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;
    axis2_hash_t *super = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, documentation, AXIS2_FAILURE);
    super = AXIS2_WODEN_DOCUMENTABLE_SUPER_OBJS(documentable, env);
    documentable_impl = INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_WODEN_DOCUMENTABLE", AXIS2_HASH_KEY_STRING));
   
    if(!documentable_impl->f_doc_elems)
    {
        documentable_impl->f_doc_elems = axis2_array_list_create(env, 0);
        if(!documentable_impl->f_doc_elems)
        {
            AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
            return AXIS2_FAILURE;
        }
    }
    return AXIS2_ARRAY_LIST_ADD(documentable_impl->f_doc_elems, env, 
            documentation);
}

axis2_array_list_t *AXIS2_CALL
axis2_woden_documentable_get_documentation_elements(
        void *documentable,
        const axis2_env_t *env)
{
    axis2_woden_documentable_impl_t *documentable_impl = NULL;
    axis2_hash_t *super = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    super = AXIS2_WODEN_DOCUMENTABLE_SUPER_OBJS(documentable, env);
    documentable_impl = INTF_TO_IMPL(axis2_hash_get(super, 
                "AXIS2_WODEN_DOCUMENTABLE", AXIS2_HASH_KEY_STRING));
   

    return documentable_impl->f_doc_elems;
}

