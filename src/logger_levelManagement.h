/**
 @file
 Diagnostics print library - logger level settings management
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_LEVELMANAGEMENT_H
#define _LOG_LEVELMANAGEMENT_H


#ifdef __cplusplus
extern "C" {
#endif


#include "logger.h"
#include "logger_common.h"


/**
 @brief from a given character get the associated LOG_LEVEL
 @details conversions types below \n
 '>' <-> LOG_LEVEL_ENTRY \n
 '<' <-> LOG_LEVEL_EXIT \n
 'i'/'I' <-> LOG_LEVEL_INFO \n
 'w'/'W' <-> LOG_LEVEL_WARN \n
 'e'/'E' <-> LOG_LEVEL_ERROR
 'f'/'F' <-> LOG_LEVEL_FATAL
 'a'/'A' <-> LOG_LEVEL_ASSERT \n
 'v'/'V' <-> LOG_LEVEL_EVENT \n
 @return returns not #LOG_LEVEL_NONE on success
 */
LOG_LEVEL loggerFlags_level_charToLevel ( char loggerChar );


/**
 @brief from a given string convert into #LOG_LEVEL_FLAGS
 @param[in] loggerLevel NULL terminated string of logger level chars
 @param[in] loggerLevelLen Number of characters in above char array to examine
 @return returns all flags from string
 */
LOG_LEVEL_FLAGS loggerFlags_level_stringToFlags ( char * loggerLevel, size_t loggerLevelLen );


/**
 @brief add #LOG_LEVEL to handlePrv
 @param[in] handlePrv handle to logger to be changed
 @param[in] loggerLevel level to be added
 */
void logger_level_add ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel );


/**
 @brief remove #LOG_LEVEL to handlePrv
 @param[in] handlePrv handle to logger to be changed
 @param[in] loggerLevel level to be removed
 */
void logger_level_remove ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel );


/**
 @brief test if #LOG_LEVEL is enabled in handlePrv
 @param[in] handlePrv handle to logger to be tested
 @param[in] loggerLevel level to test for
 @return #true on success
 */
bool logger_level_isEnabled ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel );

    
#ifdef __cplusplus
}
#endif


#endif
