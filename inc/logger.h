/**
 @file
 Diagnostics print library
 
 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_H
#define _LOG_H


#ifdef __cplusplus
extern "C" {
#endif

    
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


/* enable trace for init/term */
/* #define LOG_ENABLE_TRACE */


/**
 @enum _LOG_LEVEL
 @brief Various logger levels that can be enabled. \n
 All values are or'ed (bitwise) such that all, or none can be enabled
 \n\n
 #LOG_LEVEL_NONE No logger enabled \n
 #LOG_LEVEL_ENTRY Enable function/method entry logger - used to denote method entry logger\n
 #LOG_LEVEL_EXIT Enable function/method exit logger - used to denote method exit logger\n
 #LOG_LEVEL_INFO Enable info level logger - used for logging additional information\n
 #LOG_LEVEL_WARN Enable warnings level logger - used to denote an unwelcome situation\n
 #LOG_LEVEL_ERROR Enable error level logger - used to denote a serious but recoverable error\n
 #LOG_LEVEL_FATAL Enable fatal level logger - used to denote a critical error\n
 #LOG_LEVEL_ASSERT Enable assertion logger - used for when an assert failed\n
 #LOG_LEVEL_EVENT Enable event level logger - used for key milestone events \n
 */
typedef enum _LOG_LEVEL
{
    LOG_LEVEL_NONE    = 0U,
    LOG_LEVEL_ENTRY   = 1U,
    LOG_LEVEL_EXIT    = 2U,
    LOG_LEVEL_TRACE   = 4U,
    LOG_LEVEL_INFO    = 8U,
    LOG_LEVEL_WARN    = 16U,
    LOG_LEVEL_ERROR   = 32U,
    LOG_LEVEL_FATAL   = 64U,
    LOG_LEVEL_ASSERT  = 128U,
    LOG_LEVEL_EVENT   = 256U,
} LOG_LEVEL;


#define LOG_OUTPUT_HANDLE void*


#define LOG_OUTPUT_HANDLE_INVALID (NULL)


#ifdef LOG_ENABLE_TRACE
/**
 @brief Initialize a logger handle with a string of chars. (Use the trace version to track logger handles created that aren't released)
 @param[out] handle The returned handle to be used in subsequent calls to print logger
 @param[in] loggerLevel Where "IWEFV<>" enables all logger
 @param[in] fileName name of file on which init occured
 @param[in] lineNumber line of file on which init occured
 @return returns #true on print success
 */
bool loggerInit_trace ( LOG_OUTPUT_HANDLE * handle, LOG_LEVEL loggerLevel, const char * fileName, int lineNumber );
#define loggerInit(a,b) loggerInit_trace((a),(b), __FILE__, __LINE__)
#else
/**
 @brief Initialize a logger handle with a string of chars. Upon success calls can be made requiring a #LOG_OUTPUT_HANDLE
 @param[out] handle The returned handle to be used in subsequent calls to print logger
 @param[in] loggerLevel Where "IWEFV<>" enables all logger
 @return returns #true on print success
 */
bool loggerInit ( LOG_OUTPUT_HANDLE * handle , LOG_LEVEL loggerLevel );
#endif


#ifdef LOG_ENABLE_TRACE
/**
 @brief Terminate a logger handle. Upon success no further calls can be made using #LOG_OUTPUT_HANDLE specified in arg
 @param[in] handle The handle to be terminated
 @param[in] fileName name of file on which init occured
 @param[in] lineNumber line of file on which init occured
 @return returns #true on print success
 */
bool loggerTerm_trace ( LOG_OUTPUT_HANDLE handle, const char * fileName, int lineNumber );
#define loggerTerm(a) loggerTerm_trace((a), __FILE__, __LINE__)
#else
/**
 @brief Terminate a logger handle. Upon success no further calls can be made using #LOG_OUTPUT_HANDLE specified in arg
 @param[in] handle The handle to be terminated
 @retval #true terminated successfully
 @retval #false termination failed
 */
bool loggerTerm  ( LOG_OUTPUT_HANDLE handle );
#endif


/**
 @brief Initialize logger segment according to #loggerName
 @detail the loggerName will be cross-referenced against settings loaded from #loggerLoadIniFile. \n
 If there is a match it will load that setting. Else load value from loggerSetSeverityEnablements_Default
 @retval #true initialization successfull
 @retval #false initialization failed
 */
bool loggerInitFromFileName ( LOG_OUTPUT_HANDLE * handle, const char * loggerName, uint32_t loggerNameLen );


/**
 @brief Set the default severity enabled levels
 @details Used in conjuction with #loggerInitFromFileName when the loggerName is not found
 @param[in] loggerLevel Default logger levels to enable as standard
 */
void loggerSetSeverityEnablements_Default ( LOG_LEVEL loggerLevel );


/**
 @brief Load the logger ini file
 @detail Reads text file with $LOG_NAME = LOG_LEVELS e.g MyComponent = AFEWVI
 @param[in] filePath file path of ini settings file
 @param[in] filePathLen length of above array
 @retval #true success
 @retval #false failed
 */
bool loggerLoadIniFile ( char * filePath, size_t filePathLen );


/**
 @brief Enable logger level
 @param[in] handle Debug handle
 @param[in] addLevel logger level(s) to be enabled
 @return returns #true on success
 */
bool loggerAppendDebugLevel ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL addLevel );


/**
 @brief Disable logger level
 @param[in] handle Debug handle
 @param[in] rmLevel logger level(s) to be disabled
 @return returns #true on print success
 */
bool loggerRemoveDebugLevel ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL rmLevel );


/**
 @brief Check whether logger level(s) are enabled
 @param[in] handle Debug handle
 @param[in] isLevel logger level(s) to be checked
 @return returns #true if all logger levels in isLevel are currently enabled
 */
bool loggerIsDebugLevelEnabled ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL isLevel );


/**
 @brief Print a message
 @param[in] handle Debug handle
 @param[in] loggerLevel Debug level of which to print at. Only one value from #LOG_LEVEL must be present
 @param[in] fileName name of file of which logger print occured
 @param[in] lineNumber line of file of which logger print occured
 @param[in] functionName function from file of which logger print occured
 @param[in] fmt message format
 @param[in] ... vargs
 @return returns #true on print success
 */
bool logPrint ( LOG_OUTPUT_HANDLE handle,
                 LOG_LEVEL loggerLevel,
                 const char * fileName,
                 const int lineNumber,
                 const char * functionName,
                 const char * fmt, 
                 ... );


/**
 @brief Returns logger version
 @return version number
 */
uint32_t loggerVersion (void );

void logger_init_handle(LOG_OUTPUT_HANDLE * external_handle);

LOG_OUTPUT_HANDLE logger_get_handle(void);

LOG_OUTPUT_HANDLE * logger_get_handle_addr(void);

/**
 @def LOG_PRINT_ENTRY
 @brief print logger entry message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_ENTRY(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_ENTRY, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_EXIT
 @brief print logger exit message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_EXIT(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_EXIT, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)

/**
 @def LOG_PRINT_TRACE
 @brief print logger info message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_TRACE(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_TRACE, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_INFO
 @brief print logger info message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_INFO(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_INFO, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_WARN
 @brief print logger warn message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_WARN(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_WARN, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_ERROR
 @brief print logger error message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_ERROR(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_FATAL
 @brief print logger fatal message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_FATAL(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_FATAL, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_ASSERT
 @brief print logger assertion
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_ASSERT(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_ASSERT, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


/**
 @def LOG_PRINT_EVENT
 @brief print logger event message
 @param[in] hdl handle
 @param[in] format message format
 @param[in] vargs variable arguments
 */
#define LOG_PRINT_EVENT(hdl, format, ... ) \
do \
{ \
    logPrint (hdl, LOG_LEVEL_EVENT, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__ ); \
} while (0)


#ifdef __cplusplus
}
#endif


#endif /* _LOG_H */
