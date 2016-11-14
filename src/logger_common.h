/**
 @file
 Diagnostics print library - common defines
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_COMMON_H
#define _LOG_COMMON_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdlib.h>


/**
 @brief current logger version
 */
#define LOG_VERSION 1.0f


/**
 @enum _LOG_STATUS
 @brief returned status codes from internal logger print functions \n
 #LOG_STATUS_OK all ok \n
 #LOG_STATUS_FAILURE generic failure \n
 #LOG_STATUS_FAILURE_NOT_WHOLE_MESSAGE_PRINTED failed to print whole message \n
 #LOG_STATUS_FAILURE_ALREADY_INITIALIZED could not initialize location as it is already set up
 #LOG_STATUS_FAILURE_ALREADY_TERMINATED could not terminate location as it is already terminated
 #LOG_STATUS_FAILURE_INVALID_MESSAGE could not print, invalid message
 #LOG_STATUS_FAILURE_INVALID_PARAM invalid parameter passed into function
 */
typedef enum _LOG_STATUS
{
    LOG_STATUS_UNDEF = 0,    
    LOG_STATUS_OK,
    LOG_STATUS_FAILURE,
    LOG_STATUS_FAILURE_NOT_WHOLE_MESSAGE_PRINTED,
    LOG_STATUS_FAILURE_ALREADY_INITIALIZED,
    LOG_STATUS_FAILURE_ALREADY_TERMINATED,
    LOG_STATUS_FAILURE_INVALID_MESSAGE,
    LOG_STATUS_FAILURE_INVALID_PARAM,
    LOG_STATUS_LAST_VALUE,    
} LOG_STATUS;


typedef uint32_t LOG_LEVEL_FLAGS;


/**
 @brief internal structure holding all variables per logger handle
 */
typedef struct _LOG_HANDLE_PRV
{
    LOG_LEVEL_FLAGS loggerLevelsEnabled;
} LOG_HANDLE_PRV;



#define logger_memAlloc malloc
#define logger_memFree free


/* Enable to trace any defects in DebugPrint */
/* #define LOG_PRINT_LOG */

#ifdef LOG_PRINT_LOG
#include <stdio.h>
#define LOGPRINT_LOG(level,format... ) \
do \
{ \
    fprintf (stdout,"logger %s (%s:%d): ",level,__FUNCTION__,__LINE__); \
    fprintf (stdout, ##format); \
    fprintf (stdout, "\n"); \
} while (0)

/*
#define LOGPRINT_LOG_E(fmt, ... ) LOGPRINT_LOG("-ERROR-",fmt, ####fmt)
#define LOGPRINT_LOG_W(fmt, ... ) LOGPRINT_LOG("-WARN-",fmt, ##__VA_ARGS__)
#define LOGPRINT_LOG_I(fmt, ... ) LOGPRINT_LOG("-INFO-",fmt, ##__VA_ARGS__)
*/

#define LOGPRINT_LOG_E(fmt... ) LOGPRINT_LOG("-ERROR-",##fmt)
#define LOGPRINT_LOG_W(fmt... ) LOGPRINT_LOG("-WARN-", ##fmt)
#define LOGPRINT_LOG_I(fmt... ) LOGPRINT_LOG("-INFO-", ##fmt)
                                                       
#define LOGPRINT_ASSERT(cond) \
if ( (cond) != true ) \
{ \
    LOGPRINT_LOG_E("Assertion failure (%s:%d)",__FILE__,__LINE__); \
}
#else
    #define LOGPRINT_LOG_E(fmt, ...) {}
    #define LOGPRINT_LOG_W(fmt, ...) {}
    #define LOGPRINT_LOG_I(fmt, ...) {}
    #define LOGPRINT_ASSERT(cond) {}
#endif

    
#ifdef __cplusplus
}
#endif


#endif /* _LOG_COMMON_H */
