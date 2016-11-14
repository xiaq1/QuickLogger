/*************************************************************************


 ************************************************************************

	> File Name: testprintf.c
	> Version: Initial Draft
	> Author: Qichao
	> Mail: 87312668@qq.com 
	> Created Time: Wed 04 Jan 2017 02:41:11 PM CST
	> Last Modifided: 
	> Description: 
	> Function List: 

	> History Information Description
		Date					Author				Modification
		2017-01-04				Qichao				Created function

 ************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "loggerFacade.h"

LOG_OUTPUT_HANDLE _loggerHandle = NULL;

void test ( void )
{

	FILE * fp = fopen("test.log", "a+");
	assert(NULL != fp);

	printf("Hello\n");
	fprintf(stderr, "do_umount() done\n");
	fprintf(fp, "do_umount() done\n");
	fprintf(fp, "Haha do_umount() done\n");
	fclose(fp);
}

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
        loggerLoadIniFile(inifile, (uint32_t)strlen(inifile));
    
		/* get logger permissions for main.c and set _loggerHandle */

		loggerSetSeverityEnablements_Default ( LOG_LEVEL_ENTRY | LOG_LEVEL_EXIT | LOG_LEVEL_TRACE | LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR | LOG_LEVEL_FATAL | LOG_LEVEL_EVENT | LOG_LEVEL_ASSERT );
		LOG_INIT;

        test();

		LOG_EXIT;
		/* destroy _loggerHandle */
		LOG_TERM;
        return 0;
    }
}
