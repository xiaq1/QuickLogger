/*************************************************************************


 ************************************************************************

	> File Name: libtest.c
	> Version: Initial Draft
	> Author: Qichao
	> Mail: 87312668@qq.com 
	> Created Time: Thu 05 Jan 2017 05:34:37 PM CST
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

#include "loggerFacade.h"

void test( void )
{

	FILE * fp = fopen("libtest.log", "a+");
	assert(NULL != fp);

	printf("Hello\n");
	fprintf(stderr, "do_umount() done\n");
	fprintf(fp, "do_umount() done\n");
	fprintf(fp, "Haha do_umount() done\n");
	fclose(fp);
}
