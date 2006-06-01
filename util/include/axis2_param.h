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

#ifndef AXIS2_PARAM_H
#define AXIS2_PARAM_H

/**
 * @file axis2_param.h
 * @brief Axis2 param interface
 */

#include <axis2_utils_defines.h>
#include <axis2_env.h>
#include <axis2_hash.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct axis2_param;
struct axis2_param_ops;

/**
 * @defgroup axis2_param Handlers
 * @ingroup axis2_core_description
 * @{
 */
    
/**
  * TEXT PARAM
  */
  static const int AXIS2_TEXT_PARAM = 0;

/**
 * Field DOM_PARAM
 */
  static const int AXIS2_DOM_PARAM = 1;
       
/**
 *   \brief param ops struct
 */
AXIS2_DECLARE_DATA typedef struct axis2_param_ops
    {
    
    /**
     * Parameter name accessor
     * @return name of the param
     */
    axis2_char_t* (AXIS2_CALL *
	get_name)(struct axis2_param *param, 
			  const axis2_env_t *env);

    /**
     * Parameter value accessor
     * @return Object
     */
    void* (AXIS2_CALL *
	get_value)(struct axis2_param *param, 
		       const axis2_env_t *env);

    /**
     * param name mutator
     * @param name
     */
     axis2_status_t (AXIS2_CALL *
	 set_name)(struct axis2_param *param, 
		 	   const axis2_env_t *env, 
	 	       axis2_char_t *name);

    /**
     * Method setValue
     *
     * @param value
     */
     axis2_status_t (AXIS2_CALL *
	 set_value)(struct axis2_param *param, 
		 		const axis2_env_t *env, 
	 			void *value);

    /**
     * Method isLocked
     *
     * @return boolean
     */
     axis2_bool_t (AXIS2_CALL *
	 is_locked)(struct axis2_param *param,
		        const axis2_env_t *env);

    /**
     * Method setLocked
     *
     * @param value
     */
     axis2_status_t (AXIS2_CALL *
	 set_locked)(struct axis2_param *param,
				 const axis2_env_t *env,
				 axis2_bool_t value);

    /**
     * Method getParameterType
     *
     * @return int
     */
     int (AXIS2_CALL *
	 get_param_type)(struct axis2_param *param, 
		 			 const axis2_env_t *env);

     axis2_status_t (AXIS2_CALL *
	 set_param_type)(struct axis2_param *param, 
				     const axis2_env_t *env,
					 int type);

     axis2_status_t (AXIS2_CALL *
	 free)(struct axis2_param *param, 
	 	   const axis2_env_t *env);

    axis2_status_t (AXIS2_CALL *
    set_attributes) (
            struct axis2_param *param,
            const axis2_env_t *env,
            axis2_hash_t *attrs);

    axis2_hash_t* (AXIS2_CALL *
    get_attributes) (
            struct axis2_param *param,
            const axis2_env_t *env);
         
    axis2_status_t (AXIS2_CALL *
    value_free) (void *param_value, 
                 const axis2_env_t *env);
}axis2_param_ops_t;
 
/** 
 * \brief Parameter struct
 */
typedef struct axis2_param
{
	/** Parameter related ops */
	axis2_param_ops_t *ops;
}axis2_param_t;

/**
 * creates param struct
 */
AXIS2_EXTERN axis2_param_t* AXIS2_CALL 
axis2_param_create(const axis2_env_t *env, 
						axis2_char_t *name, 
						void *value);

#define AXIS2_PARAM_FREE(param, env) \
    ((param)->ops->free (param, env))

#define AXIS2_PARAM_SET_NAME(param, env, name) \
    ((param)->ops->set_name (param, env, name))

#define AXIS2_PARAM_GET_NAME(param, env) \
    ((param)->ops->get_name (param, env))

#define AXIS2_PARAM_SET_VALUE(param, env, value) \
    ((param)->ops->set_value (param , env, value))

#define AXIS2_PARAM_GET_VALUE(param, env) \
    ((param)->ops->get_value (param, env))

#define AXIS2_PARAM_IS_LOCKED(param, env) \
    ((param)->ops->is_locked (param, env))

#define AXIS2_PARAM_SET_LOCKED(param, env, locked) \
    ((param)->ops->set_locked (param, env, locked))

#define AXIS2_PARAM_SET_PARAM_TYPE(param, env, type) \
    ((param)->ops->set_param_type (param, env, type))
 
#define AXIS2_PARAM_GET_PARAM_TYPE(param, env) \
    ((param)->ops->get_param_type (param, env))
    
#define AXIS2_PARAM_SET_ATTRIBUTES(param, env, attrs) \
    ((param)->ops->set_attributes (param , env, attrs))

#define AXIS2_PARAM_GET_ATTRIBUTES(param, env) \
    ((param)->ops->get_attributes (param, env))
	
/** @} */
    
#ifdef __cplusplus
}
#endif

#endif    /* AXIS2_PARAM_H */
