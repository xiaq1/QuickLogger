/**
 @file
 Diagnostics print library - logger level settings management
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include "logger_levelManagement.h"

static LOG_LEVEL_FLAGS logger_level_flags ( LOG_LEVEL loggerLevel );


LOG_LEVEL loggerFlags_level_charToLevel ( char loggerChar )
{
    LOG_LEVEL loggerLevel = LOG_LEVEL_NONE;
    
    switch ( loggerChar )
    {
        case '>' :
            loggerLevel = LOG_LEVEL_ENTRY;
            break;
            
        case '<' :
            loggerLevel = LOG_LEVEL_EXIT;
            break;
            
        case 't' :
        case 'T' :
            loggerLevel = LOG_LEVEL_TRACE;
            break;
            
        case 'i' :
        case 'I' :
            loggerLevel = LOG_LEVEL_INFO;
            break;
            
        case 'w' :
        case 'W' :
            loggerLevel = LOG_LEVEL_WARN;
            break;
            
        case 'e' :
        case 'E' :
            loggerLevel = LOG_LEVEL_ERROR;
            break;
            
        case 'f' :
        case 'F' :
            loggerLevel = LOG_LEVEL_FATAL;
            break;
            
        case 'a' :
        case 'A' :
            loggerLevel = LOG_LEVEL_ASSERT;
            break;
            
        case 'v' :
        case 'V' :
            loggerLevel = LOG_LEVEL_EVENT;
            break;
            
        default :
            LOGPRINT_LOG_E("Unrecognised character: %c !!!",loggerChar);
            break;
    }
    
    return loggerLevel;
}

LOG_LEVEL_FLAGS loggerFlags_level_stringToFlags ( char * loggerLevel, size_t loggerLevelLen )
{
    LOG_LEVEL_FLAGS flags = 0U;
    
    if ( loggerLevel )
    {
        for ( size_t i=0U; i<loggerLevelLen; i++ )
        {
            if ( loggerLevel[i] != '\0' )
            {
                flags |= (LOG_LEVEL_FLAGS)loggerFlags_level_charToLevel(loggerLevel[i]);
            }
            else
            {
                break;
            }
        }
    }
    
    return flags;
}

/* convert enum to flag bit form */
static LOG_LEVEL_FLAGS logger_level_flags ( LOG_LEVEL loggerLevel )
{
    return (LOG_LEVEL_FLAGS)loggerLevel;
}

void logger_level_add ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel )
{
    if ( handlePrv )
    {
        handlePrv->loggerLevelsEnabled = handlePrv->loggerLevelsEnabled | logger_level_flags(loggerLevel);
    }
}

void logger_level_remove ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel )
{
    if ( handlePrv )
    {
        handlePrv->loggerLevelsEnabled = handlePrv->loggerLevelsEnabled & ~logger_level_flags(loggerLevel);
    }
}

bool logger_level_isEnabled ( LOG_HANDLE_PRV * handlePrv, LOG_LEVEL loggerLevel )
{
    bool loggerEnabled = false;
    
    if ( handlePrv )
    {
        if ( (handlePrv->loggerLevelsEnabled) & logger_level_flags(loggerLevel) )
        {
            loggerEnabled = true;
        }
    }
    
    return loggerEnabled;
}
