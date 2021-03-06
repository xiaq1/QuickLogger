/**
 @file
 Diagnostics print library - ini file settings reader
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOG_INI_H
#define _LOG_INI_H


#ifdef __cplusplus
extern "C" {
#endif
    

#include <stdint.h>
#include <stdbool.h>


/**
 @enum _LOG_INI_STATUS
 @brief Various logger levels that can be enabled. \n
 All values are or'ed (bitwise) such that all, or none can be enabled
 \n\n
 #LOG_INI_STATUS_UNDEF Unused status code \n
 #LOG_INI_STATUS_SUCCESS Operation successfull\n
 #LOG_INI_STATUS_INVALID_PARAMS Operation failed due to parameters given are invalid\n
 #LOG_INI_STATUS_KEY_NOT_FOUND Could not find key in section\n
 #LOG_INI_STATUS_INTERNAL_ERROR Operation failed due to an unknown internal error\n
 #LOG_INI_STATUS_LAST_VALUE Unused status code\n
 */
typedef enum _LOG_INI_STATUS
{
    LOG_INI_STATUS_UNDEF = 0,
    LOG_INI_STATUS_SUCCESS,
    LOG_INI_STATUS_INVALID_PARAMS,
    LOG_INI_STATUS_KEY_NOT_FOUND,
    LOG_INI_STATUS_INTERNAL_ERROR,
    LOG_INI_STATUS_LAST_VALUE,
} LOG_INI_STATUS;


    
/** handle pointer used to access key-values from section */
typedef void* LOG_INI_SECTIONHANDLE;


/**
 @brief Opens ini file ready for reading section key-values
 @param[in] filePath file to open
 @param[in] filePathLen length of above param
 @return #true on success
 */
bool logger_ini_initFromFile ( const char * filePath, size_t filePathLen );


/**
 @brief Closes ini file
 */
void logger_ini_term ( void );
    
    
/**
 @brief Use to detect if ini file has been opened
 @return #true if ini file is open
 */
bool logger_ini_isFileOpen ( void );


/**
 @brief Number of sections in ini file
 @detail if file hasn't been  open. This will return zero
 @return section count
 */
uint32_t logger_ini_numberOfSections ( void );


/**
 @brief Get the section handle by the section index
 @param[out] handle section handle to be used to retrieve key-values
 @param[in] sectionIndex index of sectionHandle to get (index starts at zero)
 @param[out] sectionName name of section returned (optional)
 @param[out] sectionLen length of section name returned (optional)
 @return #LOG_INI_STATUS_SUCCESS on success
 */
LOG_INI_STATUS logger_ini_sectionHandleByIndex ( LOG_INI_SECTIONHANDLE *handle, uint32_t sectionIndex, char **sectionName, size_t *sectionLen );
    
    
/**
 @brief Get the section handle by the section's name
 @param[out] handle section handle to be used to retrieve key-values
 @param[in] sectionName name of section to retrieve
 @param[in] sectionNameLen length of name of section to retrieve
 @return #LOG_INI_STATUS_SUCCESS on success
 */
LOG_INI_STATUS logger_ini_sectionHandleByName ( LOG_INI_SECTIONHANDLE *handle, const char *sectionName, size_t sectionNameLen );
    
    
/**
 @brief Get the number of key-value pairs for this section
 @param[in] handle handle of section to use
 @param[out] kvpairCount returns the value of key-value pairs (only valid if return code success)
 @return #LOG_INI_STATUS_SUCCESS on success
 */
LOG_INI_STATUS logger_ini_sectionNumberOfKeyValuePairs ( LOG_INI_SECTIONHANDLE handle, uint32_t *kvpairCount );
    
    
/**
 @brief Get the key-value pair at index
 @param[in] handle handle of section to use
 @param[in] sectionIdx index to retrieve (value range 0<->#logger_ini_sectionNumberOfKeyValuePairs-1)
 @param[out] keyName returned key name
 @param[out] keyLen returned key name length
 @param[out] valueName returned value name
 @param[out] valueLen returned value name length
 @return #LOG_INI_STATUS_SUCCESS on success
 */
LOG_INI_STATUS logger_ini_sectionRetrieveKeyValueAtIndex ( LOG_INI_SECTIONHANDLE handle, uint32_t sectionIdx, char **keyName, size_t *keyLen, char **valueName, size_t *valueLen );
    
    
/**
 @brief Get the value name from the key name
 @param[in] handle handle of section to use
 @param[in] keyName key name to look for
 @param[in] keyLen key name length
 @param[out] valueName returned value name
 @param[out] valueLen returned value name length
 @return #LOG_INI_STATUS_SUCCESS on success, #LOG_INI_STATUS_KEY_NOT_FOUND if keyName not found
 */
LOG_INI_STATUS logger_ini_sectionRetrieveValueFromKey ( LOG_INI_SECTIONHANDLE handle, char *keyName, size_t keyLen, char **valueName, size_t *valueLen );


    
#ifdef __cplusplus
}
#endif


#endif /* _LOG_INI_H */
