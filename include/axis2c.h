#ifndef AXIS2C_H
#define AXIS2C_H

/**
 * @file axis2c.h
 * @brief Axis2c specific global declarations
 */

#include <apr.h>
#include <apr_pools.h>
#include <apr_hash.h>

enum boolean_s {false, true};
typedef enum boolean_s boolean_t; 

apr_hash_t *axis2c_apr_hash_make(apr_pool_t *om_pool);                                        

#endif /* AXIS2C_H */
