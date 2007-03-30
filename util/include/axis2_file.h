/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AXIS2_FILE_H
#define AXIS2_FILE_H

#include <axis2_utils_defines.h>
#include <axutil_error.h>
#include <axutil_env.h>
#include <axis2_utils.h>
#include <platforms/axis2_platform_auto_sense.h>


#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct axis2_file axis2_file_t;

    /**
     * @defgroup axis2_file file
     * @ingroup axis2_util
     * @{
     */

    /**
     * create new file
     * @return file newly created file
     */
    AXIS2_EXTERN axis2_file_t * AXIS2_CALL
    axis2_file_create(const axutil_env_t *env);

    AXIS2_EXTERN void AXIS2_CALL
    axis2_file_free(axis2_file_t *file,
        const axutil_env_t *env);

    AXIS2_EXTERN axis2_status_t AXIS2_CALL
    axis2_file_set_name(axis2_file_t *file,
        const axutil_env_t *env,
        axis2_char_t *name);

    AXIS2_EXTERN axis2_char_t * AXIS2_CALL
    axis2_file_get_name(axis2_file_t *file,
        const axutil_env_t *env);

    AXIS2_EXTERN axis2_status_t AXIS2_CALL
    axis2_file_set_path(axis2_file_t *file,
        const axutil_env_t *env,
        axis2_char_t *path);

    AXIS2_EXTERN axis2_char_t * AXIS2_CALL
    axis2_file_get_path(axis2_file_t *file,
        const axutil_env_t *env);

    AXIS2_EXTERN axis2_status_t AXIS2_CALL
    axis2_file_set_timestamp(axis2_file_t *file,
        const axutil_env_t *env,
        AXIS2_TIME_T timestamp);

    AXIS2_EXTERN AXIS2_TIME_T AXIS2_CALL
    axis2_file_get_timestamp(axis2_file_t *file,
        const axutil_env_t *env);

    /**
     * create a newly allocated clone of the argument file
     */
    AXIS2_EXTERN axis2_file_t * AXIS2_CALL
    axis2_file_clone(axis2_file_t *file,
        const axutil_env_t *env);

#ifdef __cplusplus
}
#endif

#endif  /* AXIS2_FILE_H */


