/**
************************************************************
* @file         gizwits_protocol.h
* @brief        Corresponding gizwits_product.c header file (including product hardware and software version definition)
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#ifndef _GIZWITS_PROTOCOL_H
#define _GIZWITS_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

                                                                                                                  
#define SEND_MAX_TIME       200                     ///< 200ms resend
#define SEND_MAX_NUM        2                       ///< resend times
                                                    
#define protocol_VERSION    "00000004"              ///< protocol version
#define P0_VERSION          "00000002"              ///< P0 protocol version

/**@name Product Key  
* @{
*/
#define PRODUCT_KEY "e4da1d2ab15b45df865e48cc274f94c2"
/**@} */
/**@name Product Secret  
* @{
*/
#define PRODUCT_SECRET "4350c846498d419484a9480ad97c3c11"
               
/**@name Device status data reporting interval
* @{
*/
#define REPORT_TIME_MAX 6000 //6S
/**@} */    

#define CELLNUMMAX 7    


/**@name Whether the device is in the control class, 0 means no, 1 means yes
* @{
*/
#define DEV_IS_GATEWAY   0                    
/**@} */

/**@name Binding time
* @{
*/
#define NINABLETIME  0
/**@} */



#define MAX_PACKAGE_LEN    (sizeof(devStatus_t)+sizeof(attrFlags_t)+20)                 ///< Data buffer maximum length
#define RB_MAX_LEN          (MAX_PACKAGE_LEN*2)     ///< Maximum length of ring buffer

/**@name Data point related definition
* @{
*/
#define DO1_BYTEOFFSET                    0
#define DO1_BITOFFSET                     0
#define DO1_LEN                           1
#define DO2_BYTEOFFSET                    0
#define DO2_BITOFFSET                     1
#define DO2_LEN                           1
#define DO3_BYTEOFFSET                    0
#define DO3_BITOFFSET                     2
#define DO3_LEN                           1
#define DO4_BYTEOFFSET                    0
#define DO4_BITOFFSET                     3
#define DO4_LEN                           1
#define DO5_BYTEOFFSET                    0
#define DO5_BITOFFSET                     4
#define DO5_LEN                           1
#define DO6_BYTEOFFSET                    0
#define DO6_BITOFFSET                     5
#define DO6_LEN                           1
#define DO7_BYTEOFFSET                    0
#define DO7_BITOFFSET                     6
#define DO7_LEN                           1
#define DO8_BYTEOFFSET                    0
#define DO8_BITOFFSET                     7
#define DO8_LEN                           1
#define DO9_BYTEOFFSET                    1
#define DO9_BITOFFSET                     8
#define DO9_LEN                           1
#define DO10_BYTEOFFSET                    1
#define DO10_BITOFFSET                     9
#define DO10_LEN                           1
#define DO11_BYTEOFFSET                    1
#define DO11_BITOFFSET                     10
#define DO11_LEN                           1
#define DO12_BYTEOFFSET                    1
#define DO12_BITOFFSET                     11
#define DO12_LEN                           1
#define DO13_BYTEOFFSET                    1
#define DO13_BITOFFSET                     12
#define DO13_LEN                           1
#define DO14_BYTEOFFSET                    1
#define DO14_BITOFFSET                     13
#define DO14_LEN                           1
#define DO15_BYTEOFFSET                    1
#define DO15_BITOFFSET                     14
#define DO15_LEN                           1
#define DO16_BYTEOFFSET                    1
#define DO16_BITOFFSET                     15
#define DO16_LEN                           1
#define SEL1_BYTEOFFSET                    2
#define SEL1_BITOFFSET                     16
#define SEL1_LEN                           4
#define SEL2_BYTEOFFSET                    2
#define SEL2_BITOFFSET                     20
#define SEL2_LEN                           4
#define SEL3_BYTEOFFSET                    3
#define SEL3_BITOFFSET                     24
#define SEL3_LEN                           4
#define SEL4_BYTEOFFSET                    3
#define SEL4_BITOFFSET                     28
#define SEL4_LEN                           4
#define SEL5_BYTEOFFSET                    4
#define SEL5_BITOFFSET                     32
#define SEL5_LEN                           4
#define SEL6_BYTEOFFSET                    4
#define SEL6_BITOFFSET                     36
#define SEL6_LEN                           4
#define SEL7_BYTEOFFSET                    5
#define SEL7_BITOFFSET                     40
#define SEL7_LEN                           4
#define SEL8_BYTEOFFSET                    5
#define SEL8_BITOFFSET                     44
#define SEL8_LEN                           4
#define DI1_BYTEOFFSET                    22
#define DI1_BITOFFSET                     0
#define DI1_LEN                           1
#define DI2_BYTEOFFSET                    22
#define DI2_BITOFFSET                     1
#define DI2_LEN                           1
#define DI3_BYTEOFFSET                    22
#define DI3_BITOFFSET                     2
#define DI3_LEN                           1
#define DI4_BYTEOFFSET                    22
#define DI4_BITOFFSET                     3
#define DI4_LEN                           1
#define DI5_BYTEOFFSET                    22
#define DI5_BITOFFSET                     4
#define DI5_LEN                           1
#define DI6_BYTEOFFSET                    22
#define DI6_BITOFFSET                     5
#define DI6_LEN                           1
#define DI7_BYTEOFFSET                    22
#define DI7_BITOFFSET                     6
#define DI7_LEN                           1
#define DI8_BYTEOFFSET                    22
#define DI8_BITOFFSET                     7
#define DI8_LEN                           1
#define DI9_BYTEOFFSET                    23
#define DI9_BITOFFSET                     8
#define DI9_LEN                           1
#define DI10_BYTEOFFSET                    23
#define DI10_BITOFFSET                     9
#define DI10_LEN                           1
#define DI11_BYTEOFFSET                    23
#define DI11_BITOFFSET                     10
#define DI11_LEN                           1
#define DI12_BYTEOFFSET                    23
#define DI12_BITOFFSET                     11
#define DI12_LEN                           1
#define DI13_BYTEOFFSET                    23
#define DI13_BITOFFSET                     12
#define DI13_LEN                           1
#define DI14_BYTEOFFSET                    23
#define DI14_BITOFFSET                     13
#define DI14_LEN                           1
#define DI15_BYTEOFFSET                    23
#define DI15_BITOFFSET                     14
#define DI15_LEN                           1
#define DI16_BYTEOFFSET                    23
#define DI16_BITOFFSET                     15
#define DI16_LEN                           1

#define AO1_RATIO                         0.1
#define AO1_ADDITION                      -20
#define AO1_MIN                           0
#define AO1_MAX                           1400
#define AO2_RATIO                         0.1
#define AO2_ADDITION                      -20
#define AO2_MIN                           0
#define AO2_MAX                           1400
#define AO3_RATIO                         0.1
#define AO3_ADDITION                      -20
#define AO3_MIN                           0
#define AO3_MAX                           1400
#define AO4_RATIO                         0.1
#define AO4_ADDITION                      -20
#define AO4_MIN                           0
#define AO4_MAX                           1400
#define AO5_RATIO                         0.1
#define AO5_ADDITION                      -20
#define AO5_MIN                           0
#define AO5_MAX                           1400
#define AO6_RATIO                         0.1
#define AO6_ADDITION                      -20
#define AO6_MIN                           0
#define AO6_MAX                           1400
#define AO7_RATIO                         0.1
#define AO7_ADDITION                      -20
#define AO7_MIN                           0
#define AO7_MAX                           1400
#define AO8_RATIO                         0.1
#define AO8_ADDITION                      -20
#define AO8_MIN                           0
#define AO8_MAX                           1400
#define AI1_RATIO                         0.1
#define AI1_ADDITION                      -20
#define AI1_MIN                           0
#define AI1_MAX                           1400
#define AI2_RATIO                         0.1
#define AI2_ADDITION                      -20
#define AI2_MIN                           0
#define AI2_MAX                           1400
#define AI3_RATIO                         0.1
#define AI3_ADDITION                      -20
#define AI3_MIN                           0
#define AI3_MAX                           1400
#define AI4_RATIO                         0.1
#define AI4_ADDITION                      -20
#define AI4_MIN                           0
#define AI4_MAX                           1400
#define AI5_RATIO                         0.1
#define AI5_ADDITION                      -20
#define AI5_MIN                           0
#define AI5_MAX                           1400
#define AI6_RATIO                         0.1
#define AI6_ADDITION                      -20
#define AI6_MIN                           0
#define AI6_MAX                           1400
#define AI7_RATIO                         0.1
#define AI7_ADDITION                      -20
#define AI7_MIN                           0
#define AI7_MAX                           1400
#define AI8_RATIO                         0.1
#define AI8_ADDITION                      -20
#define AI8_MIN                           0
#define AI8_MAX                           1400
/**@} */

/** Writable data points Boolean and enumerated variables occupy byte size */
#define COUNT_W_BIT 6

/** Read-only data points Boolean and enumerated variables occupy byte size */
#define COUNT_R_BIT 2





typedef enum
{
    SEL1_VALUE0 = 0,//0
    SEL1_VALUE1 = 1,//1
    SEL1_VALUE2 = 2,//2
    SEL1_VALUE3 = 3,//3
    SEL1_VALUE4 = 4,//4
    SEL1_VALUE5 = 5,//5
    SEL1_VALUE6 = 6,//6
    SEL1_VALUE7 = 7,//7
    SEL1_VALUE8 = 8,//8
    SEL1_VALUE9 = 9,//9
    SEL1_VALUE_MAX,
} SEL1_ENUM_T;
typedef enum
{
    SEL2_VALUE0 = 0,//0
    SEL2_VALUE1 = 1,//1
    SEL2_VALUE2 = 2,//2
    SEL2_VALUE3 = 3,//3
    SEL2_VALUE4 = 4,//4
    SEL2_VALUE5 = 5,//5
    SEL2_VALUE6 = 6,//6
    SEL2_VALUE7 = 7,//7
    SEL2_VALUE8 = 8,//8
    SEL2_VALUE9 = 9,//9
    SEL2_VALUE_MAX,
} SEL2_ENUM_T;
typedef enum
{
    SEL3_VALUE0 = 0,//0
    SEL3_VALUE1 = 1,//1
    SEL3_VALUE2 = 2,//2
    SEL3_VALUE3 = 3,//3
    SEL3_VALUE4 = 4,//4
    SEL3_VALUE5 = 5,//5
    SEL3_VALUE6 = 6,//6
    SEL3_VALUE7 = 7,//7
    SEL3_VALUE8 = 8,//8
    SEL3_VALUE9 = 9,//9
    SEL3_VALUE_MAX,
} SEL3_ENUM_T;
typedef enum
{
    SEL4_VALUE0 = 0,//0
    SEL4_VALUE1 = 1,//1
    SEL4_VALUE2 = 2,//2
    SEL4_VALUE3 = 3,//3
    SEL4_VALUE4 = 4,//4
    SEL4_VALUE5 = 5,//5
    SEL4_VALUE6 = 6,//6
    SEL4_VALUE7 = 7,//7
    SEL4_VALUE8 = 8,//8
    SEL4_VALUE9 = 9,//9
    SEL4_VALUE_MAX,
} SEL4_ENUM_T;
typedef enum
{
    SEL5_VALUE0 = 0,//0
    SEL5_VALUE1 = 1,//1
    SEL5_VALUE2 = 2,//2
    SEL5_VALUE3 = 3,//3
    SEL5_VALUE4 = 4,//4
    SEL5_VALUE5 = 5,//5
    SEL5_VALUE6 = 6,//6
    SEL5_VALUE7 = 7,//7
    SEL5_VALUE8 = 8,//8
    SEL5_VALUE9 = 9,//9
    SEL5_VALUE_MAX,
} SEL5_ENUM_T;
typedef enum
{
    SEL6_VALUE0 = 0,//0
    SEL6_VALUE1 = 1,//1
    SEL6_VALUE2 = 2,//2
    SEL6_VALUE3 = 3,//3
    SEL6_VALUE4 = 4,//4
    SEL6_VALUE5 = 5,//5
    SEL6_VALUE6 = 6,//6
    SEL6_VALUE7 = 7,//7
    SEL6_VALUE8 = 8,//8
    SEL6_VALUE9 = 9,//9
    SEL6_VALUE_MAX,
} SEL6_ENUM_T;
typedef enum
{
    SEL7_VALUE0 = 0,//0
    SEL7_VALUE1 = 1,//1
    SEL7_VALUE2 = 2,//2
    SEL7_VALUE3 = 3,//3
    SEL7_VALUE4 = 4,//4
    SEL7_VALUE5 = 5,//5
    SEL7_VALUE6 = 6,//6
    SEL7_VALUE7 = 7,//7
    SEL7_VALUE8 = 8,//8
    SEL7_VALUE9 = 9,//9
    SEL7_VALUE_MAX,
} SEL7_ENUM_T;
typedef enum
{
    SEL8_VALUE0 = 0,//0
    SEL8_VALUE1 = 1,//1
    SEL8_VALUE2 = 2,//2
    SEL8_VALUE3 = 3,//3
    SEL8_VALUE4 = 4,//4
    SEL8_VALUE5 = 5,//5
    SEL8_VALUE6 = 6,//6
    SEL8_VALUE7 = 7,//7
    SEL8_VALUE8 = 8,//8
    SEL8_VALUE9 = 9,//9
    SEL8_VALUE_MAX,
} SEL8_ENUM_T;

/** Event enumeration */
typedef enum
{
  WIFI_SOFTAP = 0x00,                               ///< WiFi SOFTAP configuration event
  WIFI_AIRLINK,                                     ///< WiFi module AIRLINK configuration event
  WIFI_STATION,                                     ///< WiFi module STATION configuration event
  WIFI_OPEN_BINDING,                                ///< The WiFi module opens the binding event
  WIFI_CLOSE_BINDING,                               ///< The WiFi module closes the binding event
  WIFI_CON_ROUTER,                                  ///< The WiFi module is connected to a routing event
  WIFI_DISCON_ROUTER,                               ///< The WiFi module has been disconnected from the routing event
  WIFI_CON_M2M,                                     ///< The WiFi module has a server M2M event
  WIFI_DISCON_M2M,                                  ///< The WiFi module has been disconnected from the server M2M event
  WIFI_OPEN_TESTMODE,                               ///< The WiFi module turns on the test mode event
  WIFI_CLOSE_TESTMODE,                              ///< The WiFi module turns off the test mode event
  WIFI_CON_APP,                                     ///< The WiFi module connects to the APP event
  WIFI_DISCON_APP,                                  ///< The WiFi module disconnects the APP event
  WIFI_RSSI,                                        ///< WiFi module RSSI event
  WIFI_NTP,                                         ///< Network time event
  MODULE_INFO,                                      ///< Module information event
  TRANSPARENT_DATA,                                 ///< Transparency events
  EVENT_DO1,
  EVENT_DO2,
  EVENT_DO3,
  EVENT_DO4,
  EVENT_DO5,
  EVENT_DO6,
  EVENT_DO7,
  EVENT_DO8,
  EVENT_DO9,
  EVENT_DO10,
  EVENT_DO11,
  EVENT_DO12,
  EVENT_DO13,
  EVENT_DO14,
  EVENT_DO15,
  EVENT_DO16,
  EVENT_SEL1,
  EVENT_SEL2,
  EVENT_SEL3,
  EVENT_SEL4,
  EVENT_SEL5,
  EVENT_SEL6,
  EVENT_SEL7,
  EVENT_SEL8,
  EVENT_AO1,
  EVENT_AO2,
  EVENT_AO3,
  EVENT_AO4,
  EVENT_AO5,
  EVENT_AO6,
  EVENT_AO7,
  EVENT_AO8,
  EVENT_TYPE_MAX                                    ///< Enumerate the number of members to calculate (user accidentally deleted)
} EVENT_TYPE_T;

/** P0 Command code */
typedef enum
{
    ACTION_CONTROL_DEVICE       = 0x01,             ///< Protocol 4.10 WiFi Module Control Device WiFi Module Send
    ACTION_READ_DEV_STATUS      = 0x02,             ///< Protocol 4.8 WiFi Module Reads the current status of the device WiFi module sent
    ACTION_READ_DEV_STATUS_ACK  = 0x03,             ///< Protocol 4.8 WiFi Module Read Device Current Status Device MCU Reply
    ACTION_REPORT_DEV_STATUS    = 0x04,             ///< Protocol 4.9 device MCU to the WiFi module to actively report the current status of the device to send the MCU
    ACTION_W2D_TRANSPARENT_DATA = 0x05,             ///< WiFi to device MCU transparent
    ACTION_D2W_TRANSPARENT_DATA = 0x06,             ///< Device MCU to WiFi
} actionType_t;   

/** Protocol network time structure */
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint32_t ntp;
}protocolTime_t;
           

/** WiFi Module configuration parameters*/
typedef enum
{
  WIFI_RESET_MODE = 0x00,                           ///< WIFI module reset
  WIFI_SOFTAP_MODE,                                 ///< WIFI module softAP modeF
  WIFI_AIRLINK_MODE,                                ///< WIFI module AirLink mode
  WIFI_PRODUCTION_TEST,                             ///< MCU request WiFi module into production test mode
  WIFI_NINABLE_MODE,                                ///< MCU request module to enter binding mode
  WIFI_REBOOT_MODE,                                 ///< MCU request module reboot  
}WIFI_MODE_TYPE_T;                                

/** The protocol event type*/
typedef enum
{
  STATELESS_TYPE = 0x00,                            ///< Stateless type
  ACTION_CONTROL_TYPE,                              ///< Protocol 4.10 :WiFi module control device event
  WIFI_STATUS_TYPE,                                 ///< Protocol 4.5 :WiFi module inform the device MCU of the change event of the WiFi module status
  ACTION_W2D_TRANSPARENT_TYPE,                      ///< Protocol WiFi to device MCU transparent event
  GET_NTP_TYPE,                                     ///< Protocol 4.13 :The MCU requests access to the network time event
  GET_MODULEINFO_TYPE,                              ///< Protocol 4.9 :The MCU get module information event
  PROTOCOL_EVENT_TYPE_MAX                           ///< Count enumerated member (User donot delete)
} PROTOCOL_EVENT_TYPE_T;
     
/** Protocol command code */                                   
typedef enum                               
{                                                   
    CMD_GET_DEVICE_INTO             = 0x01,         ///< Protocol：3.1 
    ACK_GET_DEVICE_INFO             = 0x02,         ///< Protocol：3.1 
            
    CMD_ISSUED_P0                   = 0x03,         ///< Protocol：3.2 3.3 
    ACK_ISSUED_P0                   = 0x04,         ///< Protocol：3.2 3.3 
            
    CMD_REPORT_P0                   = 0x05,         ///< Protocol：3.4 
    ACK_REPORT_P0                   = 0x06,         ///< Protocol：3.4 
            
    CMD_HEARTBEAT                   = 0x07,         ///< Protocol：3.5 
    ACK_HEARTBEAT                   = 0x08,         ///< Protocol：3.5 
            
    CMD_WIFI_CONFIG                 = 0x09,         ///< Protocol：3.6 
    ACK_WIFI_CONFIG                 = 0x0A,         ///< Protocol：3.6 
            
    CMD_SET_DEFAULT                 = 0x0B,         ///< Protocol：3.7 
    ACK_SET_DEFAULT                 = 0x0C,         ///< Protocol：3.7 
            
    CMD_WIFISTATUS                  = 0x0D,         ///< Protocol：3.8 
    ACK_WIFISTATUS                  = 0x0E,         ///< Protocol：3.8 
        
    CMD_MCU_REBOOT                  = 0x0F,         ///< Protocol：4.1 
    ACK_MCU_REBOOT                  = 0x10,         ///< Protocol：4.1 
            
    CMD_ERROR_PACKAGE               = 0x11,         ///< Protocol：3.9 
    ACK_ERROR_PACKAGE               = 0x12,         ///< Protocol：3.9 

    CMD_PRODUCTION_TEST             = 0x13,         ///< Protocol：
    ACK_PRODUCTION_TEST             = 0x14,         ///< Protocol：

    CMD_NINABLE_MODE                = 0x15,         ///< Protocol：3.10
    ACK_NINABLE_MODE                = 0x16,         ///< Protocol：3.10

    CMD_GET_NTP                     = 0x17,         ///< Protocol：4.3 
    ACK_GET_NTP                     = 0x18,         ///< Protocol：4.3 


    CMD_ASK_BIGDATA                 = 0x19,         ///< Protocol：4.4
    ACK_ASK_BIGDATA                 = 0x1A,         ///< Protocol：4.4

    CMD_BIGDATA_READY               = 0x1B,         ///< Protocol：4.5
    ACK_BIGDATA_READY               = 0x1C,         ///< Protocol：4.5

    CMD_BIGDATA_SEND                = 0x1D,         ///< Protocol：4.6
    ACK_BIGDATA_SEND                = 0x1E,         ///< Protocol：4.6

    CMD_S_STOP_BIGDATA_SEND         = 0x1F,         ///< Protocol：4.7
    ACK_S_STOP_BIGDATA_SEND         = 0x20,         ///< Protocol：4.7

    CMD_D_STOP_BIGDATA_SEND         = 0x27,         ///< Protocol：4.8
    ACK_D_STOP_BIGDATA_SEND         = 0x28,         ///< Protocol：4.8

    CMD_ASK_MODULE_INFO             = 0x21,         ///< Protocol：4.9
    ACK_ASK_MODULE_INFO             = 0x22,         ///< Protocol：4.9

    CMD_ASK_AFFAIR_HANDLE           = 0x23,         ///< Protocol：4.10
    ACK_ASK_AFFAIR_HANDLE           = 0x24,         ///< Protocol：4.10

    CMD_AFFAIR_RESULT               = 0x25,         ///< Protocol：4.10
    ACK_AFFAIR_RESULT               = 0x26,         ///< Protocol：4.10

    CMD_REBOOT_MODULE               = 0x29,         ///< Protocol：3.11
    ACK_REBOOT_MODULE               = 0x2A,         ///< Protocol：3.11

    CMD_CONNECT_M2M                 = 0x2D,         ///< Protocol：for Virtualization
    ACK_CONNECT_M2M                 = 0x2E,         ///< Protocol：for Virtualization

    CMD_CONNECT_M2M_BACK            = 0x2F,         ///< Protocol：for Virtualization
    ACK_CONNECT_M2M_BACK            = 0x30,         ///< Protocol：for Virtualization

    CMD_UPLOAD_DATA                 = 0x31,         ///< Protocol：for Virtualization
    ACK_UPLOAD_DATA                 = 0x32,         ///< Protocol：for Virtualization

    CMD_UPLOAD_DATA_BACK            = 0x33,         ///< Protocol：for Virtualization
    ACK_UPLOAD_DATA_BACK            = 0x34,         ///< Protocol：for Virtualization

    CMD_DISCONNECT_M2M              = 0x35,         ///< Protocol：for Virtualization
    ACK_DISCONNECT_M2M              = 0x36,         ///< Protocol：for Virtualization

    CMD_DISCONNECT_M2M_BACK         = 0x37,         ///< Protocol：for Virtualization
    ACK_DISCONNECT_M2M_BACK         = 0x38,         ///< Protocol：for Virtualization

    CMD_RESET_SIMULATOR             = 0x39,         ///< Protocol：for Virtualization
    ACK_RESET_SIMULATOR             = 0x3A,         ///< Protocol：for Virtualization

    CMD_RESET_SIMULATOR_BACK        = 0x3B,         ///< Protocol：for Virtualization
    ACK_RESET_SIMULATOR_BACK        = 0x3C,         ///< Protocol：for Virtualization
} PROTOCOL_CMDTYPE;                                                                                  
                        
/** Illegal message type*/  
typedef enum
{
    ERROR_ACK_SUM = 0x01,                           ///< check error
    ERROR_CMD     = 0x02,                           ///< Command code error
    ERROR_OTHER   = 0x03,                           ///< other
} errorPacketsType_t;

typedef enum
{
    EXE_SUCESS                      = 0x00,
    EXE_FAILE                       = 0x01,
} execute_result;  

#pragma pack(1)

/** User Area Device State Structure */
typedef struct {
  bool valueDO1;
  bool valueDO2;
  bool valueDO3;
  bool valueDO4;
  bool valueDO5;
  bool valueDO6;
  bool valueDO7;
  bool valueDO8;
  bool valueDO9;
  bool valueDO10;
  bool valueDO11;
  bool valueDO12;
  bool valueDO13;
  bool valueDO14;
  bool valueDO15;
  bool valueDO16;
  uint32_t valueSEL1;
  uint32_t valueSEL2;
  uint32_t valueSEL3;
  uint32_t valueSEL4;
  uint32_t valueSEL5;
  uint32_t valueSEL6;
  uint32_t valueSEL7;
  uint32_t valueSEL8;
  float valueAO1;
  float valueAO2;
  float valueAO3;
  float valueAO4;
  float valueAO5;
  float valueAO6;
  float valueAO7;
  float valueAO8;
  bool valueDI1;
  bool valueDI2;
  bool valueDI3;
  bool valueDI4;
  bool valueDI5;
  bool valueDI6;
  bool valueDI7;
  bool valueDI8;
  bool valueDI9;
  bool valueDI10;
  bool valueDI11;
  bool valueDI12;
  bool valueDI13;
  bool valueDI14;
  bool valueDI15;
  bool valueDI16;
  float valueAI1;
  float valueAI2;
  float valueAI3;
  float valueAI4;
  float valueAI5;
  float valueAI6;
  float valueAI7;
  float valueAI8;
} dataPoint_t;


/** Corresponding to the protocol "4.10 WiFi module control device" in the flag " attr_flags" */ 
typedef struct {
  uint8_t flagDO1:1;
  uint8_t flagDO2:1;
  uint8_t flagDO3:1;
  uint8_t flagDO4:1;
  uint8_t flagDO5:1;
  uint8_t flagDO6:1;
  uint8_t flagDO7:1;
  uint8_t flagDO8:1;
  uint8_t flagDO9:1;
  uint8_t flagDO10:1;
  uint8_t flagDO11:1;
  uint8_t flagDO12:1;
  uint8_t flagDO13:1;
  uint8_t flagDO14:1;
  uint8_t flagDO15:1;
  uint8_t flagDO16:1;
  uint8_t flagSEL1:1;
  uint8_t flagSEL2:1;
  uint8_t flagSEL3:1;
  uint8_t flagSEL4:1;
  uint8_t flagSEL5:1;
  uint8_t flagSEL6:1;
  uint8_t flagSEL7:1;
  uint8_t flagSEL8:1;
  uint8_t flagAO1:1;
  uint8_t flagAO2:1;
  uint8_t flagAO3:1;
  uint8_t flagAO4:1;
  uint8_t flagAO5:1;
  uint8_t flagAO6:1;
  uint8_t flagAO7:1;
  uint8_t flagAO8:1;
} attrFlags_t;


/** Corresponding protocol "4.10 WiFi module control device" in the data value "attr_vals" */

typedef struct {
  uint8_t wBitBuf[COUNT_W_BIT];
  uint16_t valueAO1;
  uint16_t valueAO2;
  uint16_t valueAO3;
  uint16_t valueAO4;
  uint16_t valueAO5;
  uint16_t valueAO6;
  uint16_t valueAO7;
  uint16_t valueAO8;
} attrVals_t;

/** The flag "attr_flags (1B)" + data value "P0 protocol area" in the corresponding protocol "4.10 WiFi module control device"attr_vals(6B)" */ 
typedef struct {
    attrFlags_t attrFlags;
    attrVals_t  attrVals;
}gizwitsIssued_t;

/** Corresponding protocol "4.9 Device MCU to the WiFi module to actively report the current state" in the device status "dev_status(11B)" */ 

typedef struct {
  uint8_t wBitBuf[COUNT_W_BIT];
  uint16_t valueAO1;
  uint16_t valueAO2;
  uint16_t valueAO3;
  uint16_t valueAO4;
  uint16_t valueAO5;
  uint16_t valueAO6;
  uint16_t valueAO7;
  uint16_t valueAO8;
  uint8_t rBitBuf[COUNT_R_BIT];
  uint16_t valueAI1;
  uint16_t valueAI2;
  uint16_t valueAI3;
  uint16_t valueAI4;
  uint16_t valueAI5;
  uint16_t valueAI6;
  uint16_t valueAI7;
  uint16_t valueAI8;
} devStatus_t; 


                
/** Event queue structure */                               
typedef struct {                           
    uint8_t num;                                    ///< Number of queue member
    uint8_t event[EVENT_TYPE_MAX];                  ///< Queue member event content
}eventInfo_t;


                            
/** wifiSignal strength structure */                       
typedef struct {                           
    uint8_t rssi;                                   ///< WIFI signal strength
}moduleStatusInfo_t;                                

/** Protocol standard header structure */
typedef struct
{
    uint8_t                 head[2];                ///< The head is 0xFFFF
    uint16_t                len;                    ///< From cmd to the end of the entire packet occupied by the number of bytes
    uint8_t                 cmd;                    ///< command
    uint8_t                 sn;                     ///< 
    uint8_t                 flags[2];               ///< flag,default is 0
} protocolHead_t;

/** 4.1 WiFi module requests the device information protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 protocolVer[8];         ///< Protocol version
    uint8_t                 p0Ver[8];               ///< p0 Protocol version
    uint8_t                 hardVer[8];             ///< Hardware version
    uint8_t                 softVer[8];             ///< Software version
    uint8_t                 productKey[32];         ///< Product key
    uint16_t                ninableTime;            ///< Binding time(second)
    uint8_t                 devAttr[8];             ///< Device attribute
    uint8_t                 productSecret[32];      ///< Product secret
    uint8_t                 sum;                    ///< checksum
} protocolDeviceInfo_t;

/** Protocol common data frame(4.2、4.4、4.6、4.9、4.10) protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 sum;                    ///< checksum
} protocolCommon_t;

/** 4.3 The device MCU informs the WiFi module of the configuration mode  protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 cfgMode;                ///< Configuration parameters
    uint8_t                 sum;                    ///< checksum
} protocolCfgMode_t;

/** 4.13 The MCU requests the network time  protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 time[7];                ///< Hardware version
    uint8_t                 ntp_time[4];            ///< Software version
    uint8_t                 sum;                    ///< checksum
} protocolUTT_t;

/** WiFi module working status*/
typedef union
{
    uint16_t                value;
    struct
    {
        uint16_t            softap:1;     
        uint16_t            station:1;    
        uint16_t            onboarding:1; 
        uint16_t            binding:1;    
        uint16_t            con_route:1;  
        uint16_t            con_m2m:1;    
        uint16_t            reserve1:2;   
        uint16_t            rssi:3;       
        uint16_t            app:1;        
        uint16_t            test:1;       
        uint16_t            reserve2:3;   
    }types; 
    
} wifiStatus_t;

/** WiFi status type :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    wifiStatus_t            ststus;                 ///< WIFI status
    uint8_t                 sum;                    ///< checksum
} protocolWifiStatus_t;

/** Protocol common data frame(4.9) :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 type;                   ///< Information Type
    uint8_t                 sum;                    ///< checksum
} protocolGetModuleInfo_t;

typedef struct
{
    uint8_t                 moduleType;             ///< Information Type
    uint8_t                 serialVer[8];           ///< Serial port protocol version
    uint8_t                 hardVer[8];             ///< Hardware version
    uint8_t                 softVer[8];             ///< Software version
    uint8_t                 mac[16];                ///< mac 
    uint8_t                 ip[16];                 ///< ip
    uint8_t                 devAttr[8];             ///< Device attribute
} moduleInfo_t;

/** Protocol common data frame(4.9) :protocol structure */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    moduleInfo_t            wifiModuleInfo;         ///< WIFI module information
    uint8_t                 sum;                    ///< checksum
} protocolModuleInfo_t;


/** GPRS information of base station */
typedef struct
{
    uint16_t                    LAC_ID;             ///<LAC area ID
    uint16_t                    CellID;             ///<Base station ID
    uint8_t                     RSSI;               ///<Signal strength of base station
} gprsCellInfo_t;


/** 3.19 The basic information of the GPRS communication module  */
typedef struct
{
    uint8_t                 Type;//2G/3g/4g
    uint8_t                 Pro_ver[8];//Universal serial port protocol version
    uint8_t                 Hard_ver[8];//Hardware version
    uint8_t                 Soft_ver[8];//Software version
    uint8_t                 Device_attribute[8];//Device attribute
    uint8_t                 IMEI[16];//string
    uint8_t                 IMSI[16];//string
    uint8_t                 MCC[8];//Mobile country code
    uint8_t                 MNC[8];//Mobile network code
    uint8_t                 CellNum;//Number of base station
    uint8_t                 CellInfoLen;//Information length of base station 
    gprsCellInfo_t          GPRS_CellINFO[CELLNUMMAX];
}gprsInfo_t;

/** 4.7 Illegal message notification :protocol structure*/
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 error;                  ///< error value
    uint8_t                 sum;                    ///< checksum
} protocolErrorType_t;


/** P0 message header */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol standard header structure
    uint8_t                 action;                 ///< p0 command 
} protocolP0Head_t;


/** protocol “4.9 The device MCU reports the current status to the WiFi module” device status "dev_status(11B)"  */ 
typedef struct {
                     
    devStatus_t devStatus;                          ///< Stores the device status data
}gizwitsReport_t;

/** resend strategy structure */
typedef struct {
    uint8_t                 num;                    ///< resend times
    uint8_t                 flag;                   ///< 1,Indicates that there is a need to wait for the ACK;0,Indicates that there is no need to wait for the ACK
    uint8_t                 buf[MAX_PACKAGE_LEN];   ///< resend data buffer
    uint16_t                dataLen;                ///< resend data length
    uint32_t                sendTime;               ///< resend time
} protocolWaitAck_t;
                                                                                
/** 4.8 WiFi read device datapoint value , device ack use this struct */
typedef struct
{
    protocolHead_t          head;                   ///< Protocol head
    uint8_t                 action;                 ///< p0 action
    gizwitsReport_t         reportData;             ///< p0 data
    uint8_t                 sum;                    ///< Checksum 
} protocolReport_t;


/** Protocol main and very important struct */
typedef struct
{
    uint8_t issuedFlag;                             ///< P0 action type
    uint8_t protocolBuf[MAX_PACKAGE_LEN];           ///< Protocol data handle buffer
    uint8_t transparentBuff[MAX_PACKAGE_LEN];       ///< Transparent data storage area
    uint32_t transparentLen;                        ///< Transmission data length
    
    uint32_t sn;                                    ///< Message SN
    uint32_t timerMsCount;                          ///< Timer Count 
    protocolWaitAck_t waitAck;                      ///< Protocol wait ACK data structure
    
    eventInfo_t issuedProcessEvent;                 ///< Control events
    eventInfo_t wifiStatusEvent;                    ///< WIFI Status events
    eventInfo_t NTPEvent;                           ///< NTP events
    eventInfo_t moduleInfoEvent;                    ///< Module Info events

	gizwitsReport_t reportData;                     ///< The protocol reports data for standard product
    dataPoint_t gizCurrentDataPoint;                ///< Current device datapoints status
    dataPoint_t gizLastDataPoint;                   ///< Last device datapoints status
    moduleStatusInfo_t wifiStatusData;              ///< WIFI signal intensity
    protocolTime_t TimeNTP;                         ///< Network time information
#if MODULE_TYPE
    gprsInfo_t   gprsInfoNews;
#else  
    moduleInfo_t  wifiModuleNews;                   ///< WIFI module Info
#endif
	
        
}gizwitsProtocol_t; 

#pragma pack()

/**@name Gizwits user API interface
* @{
*/

extern uint32_t gizGetTimerCount(void);

void gizwitsInit(void);
int32_t gizwitsSetMode(uint8_t mode);
void gizwitsGetNTP(void);
int32_t gizwitsHandle(dataPoint_t *currentData);
int32_t gizwitsPassthroughData(uint8_t * gizdata, uint32_t len);
void gizwitsGetModuleInfo(void);
int32_t gizPutData(uint8_t *buf, uint32_t len);

/**@} */
#ifdef __cplusplus
}
#endif 

#endif
