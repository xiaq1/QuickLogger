/**
 @file
 Diagnostics print library - message assembly
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <time.h>
#include <stdio.h>

#include "logger.h"
#include "logger_messageAssemble.h"


#define LOG_LOG_ENTRY_FORMAT ("%s%c%s%c%s%c%s%c%s%c%s")


void logger_assemble_string ( char * string, size_t string_size, char * timestamp, char * filename, char * linenumber, char * functionname, char * severity, char * message )
{
    snprintf( (char*)(string), (string_size), LOG_LOG_ENTRY_FORMAT, \
             (char*)(timestamp), LOG_SEPERATOR_CHAR, \
             (char*)(filename), LOG_SEPERATOR_CHAR, \
             (char*)(linenumber), LOG_SEPERATOR_CHAR, \
             (char*)(functionname), LOG_SEPERATOR_CHAR, \
             (char*)(severity), LOG_SEPERATOR_CHAR, \
             (char*)(message) );
}

void loggerLevelStringFromLevel ( LOG_LEVEL level, char * stringSeverity, uint8_t stringSize )
{
    char * levelStr = NULL;
    
    switch ( level )
    {
        case LOG_LEVEL_ENTRY:
            levelStr = "-->";
            break;
            
        case LOG_LEVEL_EXIT:
            levelStr = "<--";
            break;
            
        case LOG_LEVEL_INFO:
            levelStr = "INFO";
            break;
            
        case LOG_LEVEL_WARN:
            levelStr = "WARN";
            break;
            
        case LOG_LEVEL_ERROR:
            levelStr = "ERROR";
            break;
            
        case LOG_LEVEL_FATAL:
            levelStr = "FATAL";
            break;
            
        case LOG_LEVEL_ASSERT:
            levelStr = "ASSRT";
            break;
            
        case LOG_LEVEL_EVENT:
            levelStr = "EVENT";
            break;
            
        default:
            levelStr = "?????";
            LOGPRINT_LOG_E("Unrecognised logger level %d",level);
            break;
    }
    
    snprintf((char *)stringSeverity, stringSize, "%s",(char*)levelStr);
}

void loggerGetTimeString ( char * stringTimestamp, size_t stringSize )
{
    time_t  t = time(NULL);
    struct  tm *tme = localtime(&t);
    
    snprintf((char*)stringTimestamp, (size_t)stringSize, "%02d:%02d:%02d %02d/%02d/%02d",
             tme->tm_hour, tme->tm_min, tme->tm_sec, tme->tm_mday, (tme->tm_mon+1), (tme->tm_year+1900)%1000 );
}
