/**
 @file
 Diagnostics print library - message assembly
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_MESSAGEASSEMBLE_H
#define _LOG_MESSAGEASSEMBLE_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include "logger.h"
#include "logger_common.h"


/**
 @def LOG_SEPERATOR_CHAR
 @brief character seperator used to split each aspect of logger entry
 */
#define LOG_SEPERATOR_CHAR ('|')
#define LOG_SEPERATOR_CHAR_SIZE (1)

/* sizes include terminating \0 char */
#define LOG_TIMESTAMP_SIZE        (18U)     /* size of the timestamp string */
#define LOG_FUNCTIONNAME_SIZE     (62U)
#define LOG_FILENAME_SIZE         (20U)
#define LOG_LINENUMBER_SIZE       (6U)
#define LOG_SEVERITY_SIZE         (6U)
#define LOG_MESSAGE_SIZE          (1024U)


/**
 @def LOG_MAX_LOG_CHARS
 @brief max size of user print message
 */
#define LOG_MAX_LOG_CHARS \
    ( LOG_TIMESTAMP_SIZE + \
    LOG_FUNCTIONNAME_SIZE + \
    LOG_FILENAME_SIZE + \
    LOG_LINENUMBER_SIZE + \
    LOG_SEVERITY_SIZE + \
    LOG_MESSAGE_SIZE )


/**
 @def LOG_LOG_ENTRY_SIZE
 @brief maxumum size per entry in log
 */
#define LOG_LOG_ENTRY_SIZE ( LOG_TIMESTAMP_SIZE + LOG_SEPERATOR_CHAR_SIZE + LOG_FUNCTIONNAME_SIZE + LOG_SEPERATOR_CHAR_SIZE + LOG_FILENAME_SIZE + LOG_SEPERATOR_CHAR_SIZE + LOG_LINENUMBER_SIZE + LOG_SEPERATOR_CHAR_SIZE + LOG_MAX_LOG_CHARS )


/**
 @brief from the given message properties write to string assembling output
 @param[in] string string to write to
 @param[in] string_size max chars to write into string
 @param[in] timestamp NULL terminated string detailing current momemnt of time
 @param[in] filename NULL terminated string of filename (filename without path)
 @param[in] linenumber NULL terminated string of linenumber
 @param[in] functioname NULL terminated string of functionname
 @param[in] severity NULL terminated string of severity
 @param[in] message NULL terminated string of message
 */
void logger_assemble_string ( char * string, size_t string_size, char * timestamp, char * filename, char * linenumber, char * functionname, char * severity, char * message );


/**
 @brief from a given level generate string representation
 @param[in] level logger level
 @param[out] stringSeverity returned logger level string
 @param[in] stringSize maximum chars to write to stringSeverity
 */
void loggerLevelStringFromLevel ( LOG_LEVEL level, char * stringSeverity, uint8_t stringSize );


/**
 @brief remove path from filename. leaving just the filename
 @details if filename is equal to /home/user/app/class/object.m returned string will be equal to object.m
 @param[out] stringFileName returned shorthand of filename
 @param[in] stringSize maximum number of chars to write to stringFilename
 @param[in] filename input filename with/without filepath
 */
void loggerFileNameString ( char * stringFileName, uint8_t stringSize, char * filename );



#define LOG_TIMESTAMP_CHARS_MINIMUM 17


/**
 @brief create current timestamp
 @details create in format printf("%02d:%02d:%02d %02d/%02d/%02d",hr,min,seconds,day,month,year)
 @param[out] stringTimeStamp timestamp string to write to
 @param[in] stringSize maximum number of chars to write timestamp to. must be greater than equal to #LOG_TIMESTAMP_CHARS_MINIMUM
 */
void loggerGetTimeString ( char * stringTimestamp, size_t stringSize );

    
#ifdef __cplusplus
}
#endif


#endif
