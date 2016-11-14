 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2011  Ryan Powell                                       *
 * Proprietary & Confidential                                            *
 * This file & associated documentation may not be used                  *
 * without the consent of the authors permission.                        *
 * Undocumented use this material shall be an infringement of copyright. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "test_logger_output.h"
#include "loggerFacade.h"


bool test_userVerifiedOutput ( void );
bool test_assertion_null ( void );
bool test_assertion_equals ( void );
bool test_assertion_less_greater_than ( void );
bool test_logger_output ( void );


#define LOG_MSG "!!! MSG: hello world :MSG !!!"

static LOG_OUTPUT_HANDLE _loggerHandle = LOG_OUTPUT_HANDLE_INVALID;


bool test_userVerifiedOutput ( void )
{
	bool didPass = false;
	char userInput = '\0';

#if 1
	didPass = true;
#else
	printf("\n\nDid that work? (y/n): ");

	userInput = fgetc(stdin);

	if (fgetc(stdin) != '\n')
	{
		printf("i need data in char\\n format\n");
	}
	else
	{
		switch (userInput)
		{
			case 'y':
			case 'Y':
			{
				didPass = true;
			}
            break;

			case 'n':
			case 'N':
			{
				didPass = false;
			}
            break;

			default:
			{
				printf("Unrecognised input (0x%x). Please try again\n",userInput);
				didPass = test_userVerifiedOutput();
			}
            break;
		}

		printf("\n");
	}
#endif

	return didPass;
}

bool test_assertion_null ( void )
{
	printf("\n\n*** NULL ASSERTION - MANUAL CHECK ***\n\n");
	
	printf("Testing assert NULL - assertion expected\n");	
	ASSERT_NULL((void *)1);
	printf("\n");
	
	printf("Testing assert NULL - assertion expected with msg\n");	
	ASSERT_NULL_MSG((void *)1, LOG_MSG);
	printf("\n");
	
	printf("Testing assert NULL - NO assertion expected\n");
	ASSERT_NULL(NULL);
	printf("\n");
	
	printf("Testing assert NOT_NULL - assertion expected\n");
	ASSERT_NOT_NULL(NULL);
	printf("\n");
	
	printf("Testing assert NOT_NULL - assertion expected with msg\n");
	ASSERT_NOT_NULL_MSG(NULL, LOG_MSG);
	printf("\n");
	
	printf("Testing assert NOT_NULL - NO assertion expected\n");
	ASSERT_NOT_NULL((void *)1);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_assertion_equals ( void )
{
	printf("\n\n*** ASSERTION EQUALS - MANUAL CHECK ***\n\n");
	
	printf("Testing assert equals - assertion expected\n");	
	ASSERT_EQUALS(0,1);
	printf("\n");
	
	printf("Testing assert equals - assertion expected with msg\n");	
	ASSERT_EQUALS_MSG(0,1, LOG_MSG);
	printf("\n");
	
	printf("Testing assert equals - NO assertion expected\n");	
	ASSERT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - assertion expected\n");	
	ASSERT_NOT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - assertion expected with msg\n");	
	ASSERT_NOT_EQUALS(0,0);
	printf("\n");
	
	printf("Testing assert not equals - NO assertion expected\n");	
	ASSERT_NOT_EQUALS(0,1);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_assertion_less_greater_than ( void )
{
	printf("\n\n*** ASSERTION < > - MANUAL CHECK ***\n\n");
	
	printf("Testing assert greater than - assertion expected\n");	
	ASSERT_GREATER_THAN(1,2);
	printf("\n");
	
	printf("Testing assert greater than - assertion expected with MSG\n");	
	ASSERT_GREATER_THAN_MSG(1,2, LOG_MSG);
	printf("\n");
	
	printf("Testing assert greater than-float - assertion expected with MSG\n");	
	ASSERT_GREATER_THAN_F_MSG(1.0f,2.0f, LOG_MSG);
	printf("\n");
	
	printf("Testing assert greater than - NO assertion expected\n");	
	ASSERT_GREATER_THAN(2,1);
	printf("\n");
	
	printf("Testing assert less than - assertion expected\n");	
	ASSERT_LESS_THAN(2,1);
	printf("\n");
	
	printf("Testing assert less than - assertion expected with MSG\n");	
	ASSERT_LESS_THAN_MSG(2,1, LOG_MSG);
	printf("\n");
	
	printf("Testing assert less than - NO assertion expected\n");	
	ASSERT_LESS_THAN(1,2);
	printf("\n");
	
	printf("Testing assert less than - NO assertion expected\n");	
	ASSERT_LESS_THAN_F(1.0,2.0);
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_logger_output ( void )
{
	printf("\n\n*** LOG MANUAL CHECK ***\n\n");
	
	printf("testing LOG_EVENT\n");
	LOG_EVENT("LOG EVENT - hello world");
	printf("\n");
	
	printf("testing LOG_INFO\n");
	LOG_INFO("LOG INFO - hello world");
	printf("\n");
	
	printf("testing LOG_WARN\n");
	LOG_WARN("LOG WARN - hello world");
	printf("\n");
	
	printf("testing LOG_ERROR\n");
	LOG_ERROR("LOG ERROR - hello world");
	printf("\n");
	
	printf("testing LOG_FATAL\n");
	LOG_FATAL("LOG FATAL - hello world");
	printf("\n");
	
	printf("testing LOG_ENTRY\n");
	LOG_ENTRY;
	printf("\n");
	
	printf("testing LOG_EXIT\n");
	LOG_EXIT;
	printf("\n");
	
	return test_userVerifiedOutput();
}

bool test_logger_enableChange ( void )
{
    LOG_ENABLE_TYPE(LOG_LEVEL_EVENT);
	printf("LOG_EVENT expected\n");
	LOG_EVENT("EVENT msg");
	printf("\n");
    
    LOG_DISABLE_TYPE(LOG_LEVEL_EVENT);
	printf("LOG_EVENT disabled. NO output expected\n");
	LOG_EVENT("EVENT msg");
	printf("\n");
    
    return test_userVerifiedOutput();
}

bool test_logger ( void )
{
	bool testPass = false;
    
    loggerSetSeverityEnablements_Default ( LOG_LEVEL_ENTRY | LOG_LEVEL_EXIT | LOG_LEVEL_TRACE | LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERROR | LOG_LEVEL_FATAL | LOG_LEVEL_EVENT | LOG_LEVEL_ASSERT );
    
    LOG_INIT;

	while(1) {
    
	if (test_logger_output() == false)
	{
		printf("test_logger() failed\n");
	}
	else if (test_assertion_null() == false)
	{
		printf("test_assertion_null() failed\n");
	}
	else if (test_assertion_equals() == false)
	{
		printf("test_assertion_equals() failed\n");
	}
	else if (test_assertion_less_greater_than() == false)
	{
		printf("test_assertion_less_greater_than() failed\n");
	}
    else if (test_logger_enableChange() == false)
    {
		printf("test_logger_enableChange() failed\n");
    }
	else
	{
		printf("logger & assertion checks passed manual verification\n");
		testPass = true;
	}
	sleep(1);
	}
    
    LOG_TERM;
	
	return testPass;
}
