/**
 @file
 Diagnostics print library
 
 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include <assert.h>

#include "logger.h"
#include "logger_common.h"
#include "logger_messageAssemble.h"
#include "logger_initTerm.h"
#include "logger_levelManagement.h"
#include "logger_stringUtil.h"
#include "logger_ini.h"


static LOG_LEVEL f_defaultLevel = LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR | LOG_LEVEL_FATAL | LOG_LEVEL_EVENT;
//static LOG_LEVEL f_defaultLevel = LOG_LEVEL_WARN | LOG_LEVEL_ERROR | LOG_LEVEL_FATAL | LOG_LEVEL_EVENT;
static LOG_OUTPUT_HANDLE * default_handle = NULL;

static int logger_printLog ( char * msg, int msgSize, char * fileName, int lineNumber, char * functionName, LOG_LEVEL severity );

static int logger_printLog ( char * msg, int msgSize, char * fileName, int lineNumber, char * functionName, LOG_LEVEL severity )
{
    /* plus two for the ' ' in snprintf below */
    size_t strSize = LOG_MAX_LOG_CHARS;
    char completeMessage[LOG_MAX_LOG_CHARS];
    
    for ( size_t i=0U; i<LOG_MAX_LOG_CHARS; i++ )
    {
        completeMessage[i] = '\0';
    }
    
    char strTimeStamp     [LOG_TIMESTAMP_SIZE];
    char strFileName      [LOG_FILENAME_SIZE];
    char strLineNumber    [LOG_LINENUMBER_SIZE];
    char strFunctionName  [LOG_FUNCTIONNAME_SIZE];
    char strSeverity      [LOG_SEVERITY_SIZE];
    
    char *strFileNamePtr = (char*)&strFileName;
    
    loggerGetTimeString( (char*)&strTimeStamp,    LOG_TIMESTAMP_SIZE );
    logger_string_fileNameFromPath( &strFileNamePtr, NULL, fileName, (uint32_t)strlen(fileName));
    snprintf( (char*)&strLineNumber,      LOG_LINENUMBER_SIZE,     "%d",lineNumber);
    snprintf( (char*)&strFunctionName,    LOG_FUNCTIONNAME_SIZE,   "%s",functionName);
    loggerLevelStringFromLevel ( severity, (char*)&strSeverity, LOG_SEVERITY_SIZE );
    
    logger_assemble_string(completeMessage,LOG_MAX_LOG_CHARS,(char*)strTimeStamp,(char*)strFileName,(char*)strLineNumber,(char*)strFunctionName,(char*)strSeverity,msg);
    
    /* remove any pre-terminated null chars */
    for ( uint32_t i=0U; i<LOG_MAX_LOG_CHARS-1; i++ )
    {
        if ( completeMessage[i] == '\0' )
        {
            completeMessage[i] = (char)' ';
        }
    }
    
    /* now work backwards and insert the NULL termination correctly */
    for ( size_t i=LOG_MAX_LOG_CHARS-2; i>0U; i-- )
    {
        char c = completeMessage[i];
        
        if ( c != ' ' )
        {
            strSize = i+1U;
            break;
        }
    }

    completeMessage[strSize] = '\0';
    
    LOG_TEMPLATE_SEND handler = logger_getPrintHandler();
    
    int status = (*handler)((char*)completeMessage,strSize);
    
    LOGPRINT_ASSERT(status==LOG_STATUS_OK);
    
    return status;
}

#ifdef LOG_ENABLE_TRACE
bool loggerInit_trace ( LOG_OUTPUT_HANDLE * handle , LOG_LEVEL loggerLevel, const char * fileName, int lineNumber )
#else
bool loggerInit ( LOG_OUTPUT_HANDLE * handle , LOG_LEVEL loggerLevel )
#endif
{
    bool initSuccess = false;
    
    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("Invalid handle called to %s",__FUNCTION__);
        return false;
    }
    else if ( logger_ini_isFileOpen() == false )
    {
        LOGPRINT_LOG_E("Cannot run until ini file opened. Must call loggerLoadIniFile first");
        return false;
    }
    else
    {
        /* add new logger registration info */
        LOG_HANDLE_PRV * handlePrv = logger_memAlloc ( sizeof( LOG_HANDLE_PRV ) );
        
        if ( handlePrv == NULL )
        {
            LOGPRINT_LOG_E("Malloc failure !!!");
        }
        else
        {
            handlePrv->loggerLevelsEnabled = loggerLevel;
            
            *handle = (void*)handlePrv;

            initSuccess = logger_init();

            if ( initSuccess )
            {
#ifdef LOG_ENABLE_TRACE
                LOGPRINT_LOG_I("Init: %s:%d",fileName,lineNumber);
#endif
            }
            else
            {
                *handle = LOG_OUTPUT_HANDLE_INVALID;
                logger_memFree(handlePrv);
            }
        }
    }

    return initSuccess;
}

#ifdef LOG_ENABLE_TRACE
bool loggerTerm_trace ( LOG_OUTPUT_HANDLE handle, const char * fileName, int lineNumber )
#else
bool loggerTerm  ( LOG_OUTPUT_HANDLE handle )
#endif
{
    bool termSuccess = false;
    
    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("Invalid handle called to %s",__FUNCTION__);
    }
    else
    {
        LOG_HANDLE_PRV * handlePrv = (LOG_HANDLE_PRV *)handle;
        
        termSuccess = logger_term();
        
        /* release logger resources for this handle */
        logger_memFree ( handlePrv );
    }
    
    return termSuccess;
}


bool loggerInitFromFileName ( LOG_OUTPUT_HANDLE * handle, const char * fileName, uint32_t fileNameLen )
{
    bool status = false;

    /* get the basename */
    char *baseName = malloc( sizeof(char) * fileNameLen );
    size_t baseNameLen = 0U;
    
    logger_string_fileNameFromPath ( &baseName, &baseNameLen, fileName, fileNameLen );

    if ( logger_ini_isFileOpen() && ( baseName != NULL ) )
    {
        LOG_INI_SECTIONHANDLE inihandle = NULL;
        
        logger_ini_sectionHandleByName(&inihandle, "overrides", strlen("overrides"));
        
        if ( inihandle != NULL )
        {
            /* find basename in overrides. If not found use default levels */
            char *overrideString = NULL;
            size_t overrideStringLen = 0U;
            
            logger_ini_sectionRetrieveValueFromKey(inihandle, baseName, baseNameLen, &overrideString, &overrideStringLen);
            
            if ( overrideString != NULL )
            {
                LOG_LEVEL level = loggerFlags_level_stringToFlags(overrideString,overrideStringLen);
                status = loggerInit(handle, level);
            }
            else
            {
                status = loggerInit(handle, f_defaultLevel);
            }
        }
        else
        {
            /* no ini section overrides */
            status = loggerInit(handle, f_defaultLevel);
        }

        logger_memFree(baseName);
    }
    else
    {
        LOGPRINT_LOG_W("Cannot init without file ini open");
        status = loggerInit(handle, f_defaultLevel);
    }

    return status;
}

void loggerSetSeverityEnablements_Default ( LOG_LEVEL loggerLevel )
{
    f_defaultLevel = loggerLevel;
}

bool loggerLoadIniFile ( char * filePath, size_t filePathLen )
{
    return logger_ini_initFromFile(filePath, filePathLen);
}

bool loggerAppendDebugLevel ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL addLevel )
{
    bool success = false;

    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("NULL handle called to %s (hdl=%p)",__FUNCTION__,handle);
    }
    else
    {
        LOG_HANDLE_PRV * handlePrv = (LOG_HANDLE_PRV*)handle;
        
        logger_level_add(handlePrv,addLevel);
        
        success = true;
    }

    return success;
}

bool loggerRemoveDebugLevel ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL rmLevel )
{
    bool success = false;
    
    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("NULL handle called to %s (hdl=%p)",__FUNCTION__,handle);
    }
    else
    {
        LOG_HANDLE_PRV * handlePrv = (LOG_HANDLE_PRV*)handle;
        
        logger_level_remove(handlePrv,rmLevel);
        
        success = true;
    }
    
    return success;
}

bool loggerIsDebugLevelEnabled ( LOG_OUTPUT_HANDLE handle, LOG_LEVEL isLevel )
{
    bool isEnabled = false;

    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("NULL handle called to %s (hdl=%p)",__FUNCTION__,handle);
        return isEnabled;
    }
    
    LOG_HANDLE_PRV * handlePrv = (LOG_HANDLE_PRV*)handle;
    
    if ( logger_level_isEnabled(handlePrv, isLevel) )
    {
        isEnabled = true;
    }
    
    return isEnabled;
}

bool logPrint ( LOG_OUTPUT_HANDLE handle,
                 LOG_LEVEL loggerLevel,
                 const char * fileName,
                 const int lineNumber,
                 const char * functionName,
                 const char * fmt, 
                 ... )
{
    if ( handle == NULL )
    {
        LOGPRINT_LOG_E("NULL handle called to %s from %s:%d (%s:%s:%d=%s)",__FUNCTION__,functionName,lineNumber,fileName,functionName,lineNumber,fmt);
        return false;
    }
    
    bool wasDebugOutput = false;
    
    LOG_HANDLE_PRV * handlePrv = (LOG_HANDLE_PRV*)handle;
    
    if ( logger_level_isEnabled(handlePrv, loggerLevel ) )
    {
        int logSize = LOG_MESSAGE_SIZE;
        char * logDebug[logSize];
        
        if ( fmt == NULL )
        {
            logDebug[0] = '\0';
            logSize = 0;
        }
        else
        {
            va_list arg;
            va_start(arg, fmt);
            
            vsnprintf((char*)logDebug, (size_t)logSize, fmt, arg);
            
            va_end(arg);
        }

        /* this is where the message is printed */
        if ( logger_printLog((char*)logDebug, logSize, (char*)fileName, lineNumber, (char*)functionName, loggerLevel)
            == LOG_STATUS_OK )
        {
            wasDebugOutput = true;
        }
    }
    else
    {
        /* Lie - User does not want this printed. So return success */
        /*LOGPRINT_LOG_I("(%s:%d) does not want message printed for level:%d", fileName, lineNumber, loggerLevel);*/
        wasDebugOutput = true;
    }
    
    return wasDebugOutput;
}

uint32_t loggerVersion ( void )
{
    return LOG_VERSION;
}

void logger_init_handle(LOG_OUTPUT_HANDLE * external_handle)
{
	default_handle = external_handle;
}

LOG_OUTPUT_HANDLE logger_get_handle(void)
{
	assert(NULL != default_handle);
	return *default_handle;
}

LOG_OUTPUT_HANDLE * logger_get_handle_addr(void)
{
	return default_handle;
}

void lsd_printf(const char *format, ...)
{
	va_list ap, aq;

	va_start(ap, format);
	va_copy(aq, ap);
	va_end(ap);

	LOG_PRINT_INFO(logger_get_handle(), format, aq);
}

void lsd_fprintf(FILE *stream, const char *format, ...)
{
	va_list ap, aq;

	va_start(ap, format);
	va_copy(aq, ap);
	va_end(ap);

	if (stream == stderr) {
		LOG_PRINT_ERROR(logger_get_handle(), format, aq);
	} else {
		fprintf(stream, format, aq);
	}
}
