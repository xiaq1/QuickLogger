/**
 @file
 Diagnostics print library - print-udp plugin
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include "logger_pluginUdp.h"
#include <stdbool.h>
#include <pthread.h>
#include <string.h>         /* for memset */
#include <arpa/inet.h>      /* udp */
#include <netinet/in.h>     /* udp */
#include <sys/types.h>      /* udp */
#include <sys/socket.h>     /* udp */
#include <unistd.h>         /* udp */
#include <ctype.h>          /* for isdigit() */


#define BUFLEN 32
#define NPACK 10
#define SOCKET_INVALID -1

static pthread_mutex_t f_mutex_print = PTHREAD_MUTEX_INITIALIZER;
static int f_logger_udp = SOCKET_INVALID;
static struct sockaddr_in f_logger_udp_sockaddr;

static bool logger_udp_validateIpString ( char * ipAddrStr, size_t ipAddrStrLen );



static bool logger_udp_validateIpString ( char * ipAddrStr, size_t ipAddrStrLen )
{
    bool isValidIpAddr = true;
    
    /* check all characters are valid */
    for ( uint32_t i=0U; i<ipAddrStrLen; i++ )
    {
        if ( ( isdigit(ipAddrStr[i]) == false ) && ( ipAddrStr[i] != '.' ) )
        {
            LOGPRINT_LOG_E("Invalid ip address: %s unexpected char:%c", ipAddrStr,ipAddrStr[i]);
            isValidIpAddr = false;
        }
        
        if ( ! isValidIpAddr ){ break; }
    }
    
    /* check string has four '.' characters */
    if ( isValidIpAddr )
    {
        uint32_t dotCount=0U;
        
        for ( uint32_t i=0U; i<ipAddrStrLen; i++ )
        {
            if ( ipAddrStr[i] == '.' )
            {
                dotCount += 1U;
            }
        }
        
        if ( dotCount != 3U )
        {
            LOGPRINT_LOG_E("Invalid ip address: %s expected 3 '.' in string. I have: %u", ipAddrStr,dotCount);
            isValidIpAddr = false;
        }
        
    }
    
    return isValidIpAddr;
}

LOG_STATUS logger_udp_initialize ( LOG_INI_SECTIONHANDLE paramBag )
{
    LOG_STATUS status = LOG_STATUS_FAILURE;
    
    char *ipAddress = NULL;
    size_t ipAddressLen = 0U;
    char *portStr = NULL;
    size_t portStrLen = 0U;
    
    logger_ini_sectionRetrieveValueFromKey(paramBag, "ip", strlen("ip"), &ipAddress, &ipAddressLen);
    logger_ini_sectionRetrieveValueFromKey(paramBag, "port", strlen("port"), &portStr, &portStrLen);

    if ( ( ipAddress != NULL ) || ( portStr != NULL ) )
    {
        int portInt = (uint16_t)atoi(portStr);
        
        if ( logger_udp_validateIpString(ipAddress, ipAddressLen) == false )
        {
            LOGPRINT_LOG_E("ip param invalid");
            status = LOG_STATUS_FAILURE_INVALID_PARAM;
        }
        else if ( ( portInt < 0 ) || ( portInt > 0xFFFFU ) )
        {
            LOGPRINT_LOG_E("port param invalid. Must be between 1 & 65,535 (%u)",portInt);
            status = LOG_STATUS_FAILURE_INVALID_PARAM;
        }
        else
        {
            memset((char *) &f_logger_udp_sockaddr, 0, sizeof(f_logger_udp_sockaddr));
            f_logger_udp_sockaddr.sin_family = AF_INET;
            f_logger_udp_sockaddr.sin_port = htons((uint16_t)portInt);
            
            f_logger_udp=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            
            if ( f_logger_udp == SOCKET_INVALID )
            {
                LOGPRINT_LOG_E("socket() failed");
            }
            
            else if (inet_aton(ipAddress, &f_logger_udp_sockaddr.sin_addr)==0)
            {
                LOGPRINT_LOG_E("inet_aton() failed\n");
            }
            
            else
            {
                LOGPRINT_LOG_I("Set output to udp");
                status = LOG_STATUS_OK;
            }
        }
    }
    else
    {
        LOGPRINT_LOG_E("Missing param either: ip or port");
        status = LOG_STATUS_FAILURE_INVALID_PARAM;
    }

    return status;
}


LOG_STATUS logger_udp_terminate ( void )
{
    LOG_STATUS status = LOG_STATUS_FAILURE;
    
    if ( f_logger_udp != SOCKET_INVALID )
    {
        if ( close(f_logger_udp) != 0 )
        {
            LOGPRINT_LOG_E("Fail to terminate udp");
        }
        else
        {
            LOGPRINT_LOG_I("Terminated: udp");        
            status = LOG_STATUS_OK;
        }
        
        f_logger_udp = SOCKET_INVALID;
    }
    else
    {
        LOGPRINT_LOG_I("Terminated: udp");        
        status = LOG_STATUS_FAILURE_ALREADY_TERMINATED;
    }

    return status;
}

LOG_STATUS logger_udp_transmit ( char * msg, size_t msgLen )
{
    LOG_STATUS status = LOG_STATUS_FAILURE_INVALID_MESSAGE;
    
    LOGPRINT_ASSERT(f_logger_udp!=SOCKET_INVALID);
    LOGPRINT_ASSERT(msg!=NULL);
    LOGPRINT_ASSERT(msgLen!=0U);    
    
    int flags = 0;
    size_t addrSize = sizeof(f_logger_udp_sockaddr);
    
    pthread_mutex_lock( &f_mutex_print );
    
    size_t charsSent = sendto(f_logger_udp, msg, msgLen, flags, (const struct sockaddr *)&f_logger_udp_sockaddr, (socklen_t)addrSize);
    
    pthread_mutex_unlock( &f_mutex_print );
    
    if ( charsSent >= msgLen )
    {
        status = LOG_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("Failed to send whole message. Only %zd/%zd sent",charsSent,msgLen);
    }
    
    return status;
}

char * logger_udp_name ( void )
{
    return "udp";
}
