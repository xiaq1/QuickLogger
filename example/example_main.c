
#include <stdio.h>
#include <string.h>
#include "loggerFacade.h"


void test ( void )
{
    LOG_OUTPUT_HANDLE _loggerHandle = NULL;
    
    /* get logger permissions for main.c and set _loggerHandle */
    LOG_INIT;

    LOG_ENTRY;
    
    LOG_INFO("This is an info");
    
    LOG_WARN("This is a warning");
    
    LOG_ERROR("This is an error");
    
    LOG_FATAL("This is a fatal");
    
    LOG_EXIT;
    
    /* destroy _loggerHandle */
    LOG_TERM;
}

int main(int argc, const char * argv[])
{
    if ( argc != 2 )
    {
        fprintf(stderr, "Must be called with ini file to load (%u)\n",argc);
        return 1;
    }
    else
    {
        char *inifile = (char*)argv[1];

        fprintf(stdout, "Loading ini file: %s\n",inifile);
        
        /* load the configuration file which details which files have what logging permissions */
        loggerLoadIniFile(inifile, (uint32_t)strlen(inifile));
        
        test();
        return 0;
    }
}

