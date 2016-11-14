/**
 @file
 Diagnostics print library - print-stdout plugin
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <pthread.h>
#include <stdio.h>

#include "logger_pluginStdout.h"


static pthread_mutex_t f_mutex_print = PTHREAD_MUTEX_INITIALIZER;

static FILE * f_logger_stdout = NULL;


LOG_STATUS logger_stdout_initialize ( LOG_INI_SECTIONHANDLE paramBag )
{
    LOG_STATUS status = LOG_STATUS_FAILURE_INVALID_MESSAGE;
    
    if ( f_logger_stdout == NULL )
    {
        f_logger_stdout = stdout;
        LOGPRINT_LOG_I("Set output to stdout");
        status = LOG_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("already initialized (%s)", "f_logger_stdout");
        status = LOG_STATUS_FAILURE_ALREADY_INITIALIZED;
    }

    return status;
}

LOG_STATUS logger_stdout_terminate ( void )
{
    LOG_STATUS status = LOG_STATUS_FAILURE;
    
    if ( f_logger_stdout )
    {
        f_logger_stdout = NULL;
        LOGPRINT_LOG_I("Disabled output from stdout");
        status = LOG_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("already terminated (%s)",__FUNCTION__);
        status = LOG_STATUS_FAILURE_ALREADY_TERMINATED;
    }

    return status;
}

LOG_STATUS logger_stdout_transmit ( char * msg, size_t msgLen )
{
    LOG_STATUS status = LOG_STATUS_FAILURE_INVALID_MESSAGE;
    
    LOGPRINT_ASSERT(f_logger_stdout!=NULL);
    LOGPRINT_ASSERT(msg!=NULL);
    LOGPRINT_ASSERT(msgLen!=0U);    
    
    pthread_mutex_lock( &f_mutex_print );

    int charsPrinted = fprintf(f_logger_stdout, "%s\n",msg);

    pthread_mutex_unlock( &f_mutex_print );

    if ( charsPrinted >= msgLen )
    {
        status = LOG_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("Failed to print whole message. Only %d/%zd printed",charsPrinted,msgLen);
    }
    
    return status;
}

char* logger_stdout_name ( void )
{
    return "stdout";
}
