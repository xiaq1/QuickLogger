/**
 @file
 Diagnostics print library - plugin delegate interface specification
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_TEMPLATE_H
#define _LOG_TEMPLATE_H


#ifdef __cplusplus
extern "C" {
#endif


#include "logger_common.h"
#include "logger_ini.h"


/**
 @brief initialization of debug output. Must set up any prerequisites to printing at the moment this is called
 @param[in] parambag specified within each plugin header as LOG_PRINT_INIT_\#pluginname
 @return LOG_STATUS_OK on success
 */
typedef LOG_STATUS (*LOG_TEMPLATE_INIT)( LOG_INI_SECTIONHANDLE paramBag );


/**
 @brief terminate debug output & destroy any connections established at initialization
 @return LOG_STATUS_OK on success
 */
typedef LOG_STATUS (*LOG_TEMPLATE_TERM)(void);


/**
 @brief print message to output
 @param[in] msg string to print
 @param[in] msgLen number of characters in msg
 @return LOG_STATUS_OK on success
 */
typedef LOG_STATUS (*LOG_TEMPLATE_SEND)( char * msg, size_t msgLen );


/**
 @brief returns name identifier for plugin
 @detail name returned must be unique amongst all plugins. Name is used to select plugin by comparing this value to section name [output=mypluginname]. In this example. This function would have to return 'mypluginname' to be selected as the output according to the loaded ini file
 @return name of plugin
 */
typedef char* (*LOG_TEMPLATE_NAME)( void );


#ifdef __cplusplus
}
#endif


#endif /* _LOG_TEMPLATE_H */
