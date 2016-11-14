/*************************************************************************


 ************************************************************************

	> File Name: main.c
	> Version: Initial Draft
	> Author: Qichao
	> Mail: 87312668@qq.com 
	> Created Time: Thu 05 Jan 2017 05:41:52 PM CST
	> Last Modifided: 
	> Description: 
	> Function List: 

	> History Information Description
		Date					Author				Modification
		2017-01-05				Qichao				Created function

 ************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stdarg.h>

#include "loggerFacade.h"

LOG_OUTPUT_HANDLE _loggerHandle = NULL;

extern void test(void);

int main(int argc, const char * argv[])
{
    if ( argc != 2 )
    {
        fprintf(stderr, "Must be called with ini file to load (%u)\n",argc);
        return 1;
    } else {
        char *inifile = (char*)argv[1];

        fprintf(stdout, "Loading ini file: %s\n",inifile);
        
        /* load the configuration file which details which files have what logging permissions */
		INIT_LOGGER_LIB(_loggerHandle, inifile);
		printf("Test start!\n");
		fprintf(stderr, "Test start!\n");
        test();
		printf("Test done!\n");
		fprintf(stderr, "Test done!\n");
		EXIT_LOGGER_LIB;

        return 0;
    }
}
