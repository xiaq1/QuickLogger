/**
 @file
 Logger print library wrapper
 
 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */

 
#ifndef _LOGFACADE_H
#define _LOGFACADE_H


#ifdef __cplusplus
extern "C" {
#endif


/** comment line to disable logging */

#define diy_fprintf(p, fmt, ...)	\
	do {	\
		char _tpm[1024] = {0,};	\
		snprintf(_tpm, 1024, fmt, ##__VA_ARGS__);	\
		fputs(_tpm, p);	\
	} while(0)

#define LOG_ENABLED

#ifdef LOG_ENABLED


#include <string.h>
#include "logger.h"


#define LOG_INIT   loggerInitFromFileName(&_loggerHandle, __FILE__, strlen(__FILE__))
#define LOG_TERM      loggerTerm(_loggerHandle)
#define LOG_ENABLE_TYPE(a)  loggerAppendDebugLevel(_loggerHandle, (a))
#define LOG_DISABLE_TYPE(a) loggerRemoveDebugLevel(_loggerHandle, (a))

#define LOG_ENTRY LOG_PRINT_ENTRY(_loggerHandle, NULL)
#define LOG_EXIT LOG_PRINT_EXIT(_loggerHandle, NULL)

#define LOG_TRACE(format, ... )	LOG_PRINT_TRACE(_loggerHandle, format, ##__VA_ARGS__)
#define LOG_INFO(format, ... ) LOG_PRINT_INFO(_loggerHandle, format, ##__VA_ARGS__ )
#define LOG_WARN(format, ... ) LOG_PRINT_WARN(_loggerHandle, format, ##__VA_ARGS__ )
#define LOG_ERROR(format, ... ) LOG_PRINT_ERROR(_loggerHandle, format, ##__VA_ARGS__ )
#define LOG_FATAL(format, ... ) LOG_PRINT_FATAL(_loggerHandle, format, ##__VA_ARGS__ )
#define LOG_ASSERT(format, ... ) LOG_PRINT_ASSERT(_loggerHandle, format, ##__VA_ARGS__ )
#define LOG_EVENT(format, ... ) LOG_PRINT_EVENT(_loggerHandle, format, ##__VA_ARGS__ )

#define LOGLIB_INIT   loggerInitFromFileName(logger_get_handle_addr(), __FILE__, strlen(__FILE__))
#define LOGLIB_TERM      loggerTerm(logger_get_handle())
#define LOGLIB_ENABLE_TYPE(a)  loggerAppendDebugLevel(logger_get_handle(), (a))
#define LOGLIB_DISABLE_TYPE(a) loggerRemoveDebugLevel(logger_get_handle(), (a))

#define LOGLIB_ENTRY LOG_PRINT_ENTRY(logger_get_handle(), NULL)
#define LOGLIB_EXIT LOG_PRINT_EXIT(logger_get_handle(), NULL)
#define LOGLIB_TRACE(format, ... ) LOG_PRINT_TRACE(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_INFO(format, ... ) LOG_PRINT_INFO(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_WARN(format, ... ) LOG_PRINT_WARN(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_ERROR(format, ... ) LOG_PRINT_ERROR(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_FATAL(format, ... ) LOG_PRINT_FATAL(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_ASSERT(format, ... ) LOG_PRINT_ASSERT(logger_get_handle(), format, ##__VA_ARGS__ )
#define LOGLIB_EVENT(format, ... ) LOG_PRINT_EVENT(logger_get_handle(), format, ##__VA_ARGS__ )

/* ASSERTIONS */
#define ASSERT_NULL(a) \
do { \
    if ((a)!=NULL) \
    { \
        LOG_ASSERT("ASSERT_NULL "); \
    } \
} while (0)

#define ASSERT_NULL_MSG(a,format, ...) \
do { \
    if ((a)!=NULL) \
    { \
        LOG_ASSERT("ASSERT_NULL " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_NULL(a) \
do { \
    if ((a)==NULL) \
    { \
        LOG_ASSERT("ASSERT_NOT_NULL "); \
    } \
} while (0)


#define ASSERT_NOT_NULL_MSG(a,format, ...) \
do { \
    if ((a)==NULL) \
    { \
        LOG_ASSERT("ASSERT_NOT_NULL " format, ##__VA_ARGS__ ); \
    } \
} while (0)

#define ASSERT_true(a) \
do { \
    if ((a)!=true) \
    { \
        LOG_ASSERT("ASSERT_true "); \
    } \
} while (0)		

#define ASSERT_true_MSG(a,format, ...) \
do { \
    if ((a)!=true) \
    { \
    LOG_ASSERT("ASSERT_true " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_false(a) \
do { \
    if ((a)!=false) \
    { \
        LOG_ASSERT("ASSERT_false "); \
    } \
} while (0)		

#define ASSERT_false_MSG(a,format, ...) \
do { \
    if ((a)!=false) \
    { \
        LOG_ASSERT("ASSERT_false " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_ZERO(a) \
do { \
    if ((a)!=0) \
    { \
        LOG_ASSERT("ASSERT_ZERO "); \
    } \
} while (0)		

#define ASSERT_ZERO_MSG(a,format, ...) \
do { \
    if ((a)!=0) \
    { \
        LOG_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_ZERO(a) \
do { \
    if ((a)==0) \
    { \
        LOG_ASSERT("ASSERT_NOT_ZERO "); \
    } \
} while (0)		

#define ASSERT_NOT_ZERO_MSG(a,format, ...) \
do { \
    if ((a)==0) \
    { \
        LOG_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_ZERO_F(a) \
do { \
    if ((a)==0.0f) \
    { \
        LOG_ASSERT("ASSERT_NOT_ZERO "); \
    } \
} while (0)		

#define ASSERT_NOT_ZERO_F_MSG(a,format, ...) \
do { \
    if ((a)==0.0f) \
    { \
        LOG_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_EQUALS(a,b) \
do { \
    if ((a)!=(b)) \
    { \
        LOG_ASSERT("ASSERT_EQUALS %d!=%d",a,b); \
    } \
} while (0)		

#define ASSERT_EQUALS_MSG(a,b,format, ...) \
do { \
    if ((a)!=(b)) \
    { \
        LOG_ASSERT("ASSERT_EQUALS %d!=%d",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_EQUALS_F(a,b) \
do { \
    if ((a)!=(b)) \
    { \
        LOG_ASSERT("ASSERT_EQUALS %f!=%f",a,b); \
    } \
} while (0)		

#define ASSERT_EQUALS_F_MSG(a,b,format, ...) \
do { \
    if ((a)!=(b)) \
    { \
        LOG_ASSERT("ASSERT_EQUALS %f!=%f",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_EQUALS(a,b) \
do { \
    if ((a)==(b)) \
    { \
        LOG_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
    } \
} while (0)		

#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...) \
do { \
    if ((a)==(b)) \
    { \
        LOG_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_EQUALS(a,b) \
do { \
    if ((a)==(b)) \
    { \
        LOG_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
    } \
} while (0)		

#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...) \
do { \
if ((a)==(b)) \
    { \
        LOG_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_GREATER_THAN(a,b) \
do { \
    if ((a)<=(b)) \
    { \
        LOG_ASSERT("ASSERT_GREATER_THAN %d<=%d",a,b); \
    } \
} while (0)		

#define ASSERT_GREATER_THAN_MSG(a,b,format, ...) \
do { \
    if ((a)<=(b)) \
    { \
        LOG_ASSERT("ASSERT_GREATER_THAN %d<=%d",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_GREATER_THAN_F(a,b) \
do { \
    if ((a)<=(b)) \
    { \
        LOG_ASSERT("ASSERT_GREATER_THAN %f<=%f",a,b); \
    } \
} while (0)		

#define ASSERT_GREATER_THAN_F_MSG(a,b,format, ...) \
do { \
if ((a)<=(b)) \
    { \
        LOG_ASSERT("ASSERT_GREATER_THAN %f<=%f",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_LESS_THAN(a,b) \
do { \
    if ((a)>=(b)) \
    { \
        LOG_ASSERT("ASSERT_LESS_THAN %d>=%d",a,b); \
    } \
} while (0)		

#define ASSERT_LESS_THAN_MSG(a,b,format, ...) \
do { \
    if ((a)>=(b)) \
    { \
        LOG_ASSERT("ASSERT_LESS_THAN %d>=%d",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_LESS_THAN_F(a,b) \
do { \
    if ((a)>=(b)) \
    { \
        LOG_ASSERT("ASSERT_LESS_THAN %f>=%f",a,b); \
    } \
} while (0)		

#define ASSERT_LESS_THAN_F_MSG(a,b,format, ...) \
do { \
    if ((a)>=(b)) \
    { \
        LOG_ASSERT("ASSERT_LESS_THAN %f>=%f",a,b); \
        LOG_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define LOG_ERROR_WRAPPER(file, format, ...) \
	do {	\
		if (file == stderr) {	\
			LOG_ERROR(format, ##__VA_ARGS__);	\
		} else {	\
			diy_fprintf(file, format, ##__VA_ARGS__);	\
		}	\
	} while(0)

#define LOGLIB_ERROR_WRAPPER(file, format, ...) \
	do {	\
		if (file == stderr) {	\
			LOGLIB_ERROR(format, ##__VA_ARGS__);	\
		} else {	\
			diy_fprintf(file, format, ##__VA_ARGS__);	\
		}	\
	} while(0)

#else /* NO LOG */


#define LOG_INIT {}
#define LOG_TERM {}
#define LOG_ENABLE_TYPE(a)  {}
#define LOG_DISABLE_TYPE(a) {}

#define LOG_ENTRY {}
#define LOG_EXIT {}

#define LOG_TRACE(format, ... )	{}
#define LOG_INFO(format, ... )  {}
#define LOG_WARN(format, ... )  {}
#define LOG_ERROR(format, ... )  {}
#define LOG_FATAL(format, ... )  {}
#define LOG_ASSERT(format, ... )  {}
#define LOG_EVENT(format, ... )  {}

#define LOGLIB_ENTRY {}
#define LOGLIB_EXIT {}
#define LOGLIB_TRACE(format, ... )  {}
#define LOGLIB_INFO(format, ... )  {}
#define LOGLIB_WARN(format, ... )  {}
#define LOGLIB_ERROR(format, ... )  {}
#define LOGLIB_FATAL(format, ... )  {}
#define LOGLIB_ASSERT(format, ... )  {}
#define LOGLIB_EVENT(format, ... )  {}

/* ASSERTIONS */
#define ASSERT_NULL(a) {(a);} /* keep original expression-incase side-effects were intended */
#define ASSERT_NULL_MSG(a,format, ...) {}
#define ASSERT_NOT_NULL(a)  {(a);}
#define ASSERT_NOT_NULL_MSG(a,format, ...)  {}
#define ASSERT_true(a)  {(a);}
#define ASSERT_true_MSG(a,format, ...)  {(a);}
#define ASSERT_false(a)  {(a);}
#define ASSERT_false_MSG(a,format, ...)  {(a);}
#define ASSERT_ZERO(a)  {(a);}
#define ASSERT_ZERO_MSG(a,format, ...)  {(a);}
#define ASSERT_NOT_ZERO(a)  {(a);}
#define ASSERT_NOT_ZERO_MSG(a,format, ...)  {}
#define ASSERT_NOT_ZERO_F(a)  {(a);}
#define ASSERT_NOT_ZERO_F_MSG(a,format, ...)  {}
#define ASSERT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_EQUALS_MSG(a,b,format, ...)  {}
#define ASSERT_EQUALS_F(a,b)  {(a);(b);}
#define ASSERT_EQUALS_F_MSG(a,b,format, ...)  {}
#define ASSERT_NOT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_NOT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_GREATER_THAN(a,b)  {(a);(b);}
#define ASSERT_GREATER_THAN_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_GREATER_THAN_F(a,b)  {(a);(b);}
#define ASSERT_GREATER_THAN_F_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_LESS_THAN(a,b)  {(a);(b);}
#define ASSERT_LESS_THAN_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_LESS_THAN_F(a,b)  {(a);(b);}
#define ASSERT_LESS_THAN_F_MSG(a,b,format, ...)  {(a);(b);}

#define LOG_ERROR_WRAPPER(file, format, ...) \
	do {	\
		diy_fprintf(file, format, ##__VA_ARGS__);	\
	} while(0)

#define LOGLIB_ERROR_WRAPPER(file, format, ...) \
	do {	\
		diy_fprintf(file, format, ##__VA_ARGS__);	\
	} while(0)

#endif /* LOG_ENABLED */

#define INIT_LOGGER(inifile)	\
	do {	\
		loggerLoadIniFile(inifile, (uint32_t)strlen(inifile));	\
		LOG_INIT;	\
	} while (0)


#define EXIT_LOGGER	\
	do {	\
		LOG_EXIT;	\
		LOG_TERM;	\
	} while(0)

#define INIT_LOGGER_LIB(external_handle_name, inifile)	\
	do {	\
		logger_init_handle(&external_handle_name);	\
		loggerLoadIniFile(inifile, (uint32_t)strlen(inifile));	\
		LOGLIB_INIT;	\
	} while (0)


#define EXIT_LOGGER_LIB	\
	do {	\
		LOGLIB_EXIT;	\
		LOGLIB_TERM;	\
	} while(0)


void lsd_printf(const char *format, ...);

void lsd_fprintf(FILE *stream, const char *format, ...);

#ifdef __cplusplus
}
#endif


#endif /* _LOG_H */
