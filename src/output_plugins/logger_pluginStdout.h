/**
 @file
 Diagnostics print library - print-stdout plugin
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_PLUGINSTDOUT_H
#define _LOG_PLUGINSTDOUT_H


#ifdef __cplusplus
extern "C" {
#endif


#include "logger_template.h"
#include "logger_common.h"


LOG_STATUS logger_stdout_initialize ( LOG_INI_SECTIONHANDLE paramBag );
LOG_STATUS logger_stdout_terminate ( void );
LOG_STATUS logger_stdout_transmit ( char * msg, size_t msgLen );
char* logger_stdout_name ( void );
    
    
#ifdef __cplusplus
}
#endif


#endif /* _LOG_PLUGINSTDOUT_H */
