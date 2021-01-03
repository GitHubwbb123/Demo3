/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization 
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

#include <stdio.h>
#include <string.h>
#include "hal_uart.h"
#include "gizwits_product.h"
#include "common.h"

static uint32_t timerMsCount;

/** User area the current device state structure*/
extern dataPoint_t currentDataPoint;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_DO1:
        currentDataPoint.valueDO1 = dataPointPtr->valueDO1;
        GIZWITS_LOG("Evt: EVENT_DO1 %d \n", currentDataPoint.valueDO1);
        if(0x01 == currentDataPoint.valueDO1)
        {
          //user handle
          P2DIR|=BIT0;
          P2OUT&=~BIT0;
        }
        else
        {
          //user handle  
          P2DIR|=BIT0;
          P2OUT|=BIT0;
        }
        break;
      case EVENT_DO2:
        currentDataPoint.valueDO2 = dataPointPtr->valueDO2;
        GIZWITS_LOG("Evt: EVENT_DO2 %d \n", currentDataPoint.valueDO2);
        if(0x01 == currentDataPoint.valueDO2)
        {
          //user handle
          P2DIR|=BIT1;
          P2OUT&=~BIT1;
        }
        else
        {
          //user handle  
          P2DIR|=BIT1;
          P2OUT|=BIT1;
        }
        break;
      case EVENT_DO3:
        currentDataPoint.valueDO3 = dataPointPtr->valueDO3;
        GIZWITS_LOG("Evt: EVENT_DO3 %d \n", currentDataPoint.valueDO3);
        if(0x01 == currentDataPoint.valueDO3)
        {
          //user handle
          P2DIR|=BIT2;
          P2OUT&=~BIT2;
        }
        else
        {
          //user handle  
          P2DIR|=BIT2;
          P2OUT|=BIT2;
        }
        break;
      case EVENT_DO4:
        currentDataPoint.valueDO4 = dataPointPtr->valueDO4;
        GIZWITS_LOG("Evt: EVENT_DO4 %d \n", currentDataPoint.valueDO4);
        if(0x01 == currentDataPoint.valueDO4)
        {
          //user handle
          P2DIR|=BIT3;
          P2OUT&=~BIT3;
        }
        else
        {
          //user handle  
          P2DIR|=BIT3;
          P2OUT|=BIT3;
        }
        break;
      case EVENT_DO5:
        currentDataPoint.valueDO5 = dataPointPtr->valueDO5;
        GIZWITS_LOG("Evt: EVENT_DO5 %d \n", currentDataPoint.valueDO5);
        if(0x01 == currentDataPoint.valueDO5)
        {
          //user handle
          P6DIR|=BIT7;
          P6OUT&=~BIT7;
        }
        else
        {
          //user handle  
          P6DIR|=BIT7;
          P6OUT|=BIT7;
        }
        break;
      case EVENT_DO6:
        currentDataPoint.valueDO6 = dataPointPtr->valueDO6;
        GIZWITS_LOG("Evt: EVENT_DO6 %d \n", currentDataPoint.valueDO6);
        if(0x01 == currentDataPoint.valueDO6)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO7:
        currentDataPoint.valueDO7 = dataPointPtr->valueDO7;
        GIZWITS_LOG("Evt: EVENT_DO7 %d \n", currentDataPoint.valueDO7);
        if(0x01 == currentDataPoint.valueDO7)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO8:
        currentDataPoint.valueDO8 = dataPointPtr->valueDO8;
        GIZWITS_LOG("Evt: EVENT_DO8 %d \n", currentDataPoint.valueDO8);
        if(0x01 == currentDataPoint.valueDO8)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO9:
        currentDataPoint.valueDO9 = dataPointPtr->valueDO9;
        GIZWITS_LOG("Evt: EVENT_DO9 %d \n", currentDataPoint.valueDO9);
        if(0x01 == currentDataPoint.valueDO9)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO10:
        currentDataPoint.valueDO10 = dataPointPtr->valueDO10;
        GIZWITS_LOG("Evt: EVENT_DO10 %d \n", currentDataPoint.valueDO10);
        if(0x01 == currentDataPoint.valueDO10)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO11:
        currentDataPoint.valueDO11 = dataPointPtr->valueDO11;
        GIZWITS_LOG("Evt: EVENT_DO11 %d \n", currentDataPoint.valueDO11);
        if(0x01 == currentDataPoint.valueDO11)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO12:
        currentDataPoint.valueDO12 = dataPointPtr->valueDO12;
        GIZWITS_LOG("Evt: EVENT_DO12 %d \n", currentDataPoint.valueDO12);
        if(0x01 == currentDataPoint.valueDO12)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO13:
        currentDataPoint.valueDO13 = dataPointPtr->valueDO13;
        GIZWITS_LOG("Evt: EVENT_DO13 %d \n", currentDataPoint.valueDO13);
        if(0x01 == currentDataPoint.valueDO13)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO14:
        currentDataPoint.valueDO14 = dataPointPtr->valueDO14;
        GIZWITS_LOG("Evt: EVENT_DO14 %d \n", currentDataPoint.valueDO14);
        if(0x01 == currentDataPoint.valueDO14)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO15:
        currentDataPoint.valueDO15 = dataPointPtr->valueDO15;
        GIZWITS_LOG("Evt: EVENT_DO15 %d \n", currentDataPoint.valueDO15);
        if(0x01 == currentDataPoint.valueDO15)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_DO16:
        currentDataPoint.valueDO16 = dataPointPtr->valueDO16;
        GIZWITS_LOG("Evt: EVENT_DO16 %d \n", currentDataPoint.valueDO16);
        if(0x01 == currentDataPoint.valueDO16)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;

      case EVENT_SEL1:
        currentDataPoint.valueSEL1 = dataPointPtr->valueSEL1;
        GIZWITS_LOG("Evt: EVENT_SEL1 %d\n", currentDataPoint.valueSEL1);
        switch(currentDataPoint.valueSEL1)
        {
          case SEL1_VALUE0:
            //user handle
            break;
          case SEL1_VALUE1:
            //user handle
            break;
          case SEL1_VALUE2:
            //user handle
            break;
          case SEL1_VALUE3:
            //user handle
            break;
          case SEL1_VALUE4:
            //user handle
            break;
          case SEL1_VALUE5:
            //user handle
            break;
          case SEL1_VALUE6:
            //user handle
            break;
          case SEL1_VALUE7:
            //user handle
            break;
          case SEL1_VALUE8:
            //user handle
            break;
          case SEL1_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL2:
        currentDataPoint.valueSEL2 = dataPointPtr->valueSEL2;
        GIZWITS_LOG("Evt: EVENT_SEL2 %d\n", currentDataPoint.valueSEL2);
        switch(currentDataPoint.valueSEL2)
        {
          case SEL2_VALUE0:
            //user handle
            break;
          case SEL2_VALUE1:
            //user handle
            break;
          case SEL2_VALUE2:
            //user handle
            break;
          case SEL2_VALUE3:
            //user handle
            break;
          case SEL2_VALUE4:
            //user handle
            break;
          case SEL2_VALUE5:
            //user handle
            break;
          case SEL2_VALUE6:
            //user handle
            break;
          case SEL2_VALUE7:
            //user handle
            break;
          case SEL2_VALUE8:
            //user handle
            break;
          case SEL2_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL3:
        currentDataPoint.valueSEL3 = dataPointPtr->valueSEL3;
        GIZWITS_LOG("Evt: EVENT_SEL3 %d\n", currentDataPoint.valueSEL3);
        switch(currentDataPoint.valueSEL3)
        {
          case SEL3_VALUE0:
            //user handle
            break;
          case SEL3_VALUE1:
            //user handle
            break;
          case SEL3_VALUE2:
            //user handle
            break;
          case SEL3_VALUE3:
            //user handle
            break;
          case SEL3_VALUE4:
            //user handle
            break;
          case SEL3_VALUE5:
            //user handle
            break;
          case SEL3_VALUE6:
            //user handle
            break;
          case SEL3_VALUE7:
            //user handle
            break;
          case SEL3_VALUE8:
            //user handle
            break;
          case SEL3_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL4:
        currentDataPoint.valueSEL4 = dataPointPtr->valueSEL4;
        GIZWITS_LOG("Evt: EVENT_SEL4 %d\n", currentDataPoint.valueSEL4);
        switch(currentDataPoint.valueSEL4)
        {
          case SEL4_VALUE0:
            //user handle
            break;
          case SEL4_VALUE1:
            //user handle
            break;
          case SEL4_VALUE2:
            //user handle
            break;
          case SEL4_VALUE3:
            //user handle
            break;
          case SEL4_VALUE4:
            //user handle
            break;
          case SEL4_VALUE5:
            //user handle
            break;
          case SEL4_VALUE6:
            //user handle
            break;
          case SEL4_VALUE7:
            //user handle
            break;
          case SEL4_VALUE8:
            //user handle
            break;
          case SEL4_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL5:
        currentDataPoint.valueSEL5 = dataPointPtr->valueSEL5;
        GIZWITS_LOG("Evt: EVENT_SEL5 %d\n", currentDataPoint.valueSEL5);
        switch(currentDataPoint.valueSEL5)
        {
          case SEL5_VALUE0:
            //user handle
            break;
          case SEL5_VALUE1:
            //user handle
            break;
          case SEL5_VALUE2:
            //user handle
            break;
          case SEL5_VALUE3:
            //user handle
            break;
          case SEL5_VALUE4:
            //user handle
            break;
          case SEL5_VALUE5:
            //user handle
            break;
          case SEL5_VALUE6:
            //user handle
            break;
          case SEL5_VALUE7:
            //user handle
            break;
          case SEL5_VALUE8:
            //user handle
            break;
          case SEL5_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL6:
        currentDataPoint.valueSEL6 = dataPointPtr->valueSEL6;
        GIZWITS_LOG("Evt: EVENT_SEL6 %d\n", currentDataPoint.valueSEL6);
        switch(currentDataPoint.valueSEL6)
        {
          case SEL6_VALUE0:
            //user handle
            break;
          case SEL6_VALUE1:
            //user handle
            break;
          case SEL6_VALUE2:
            //user handle
            break;
          case SEL6_VALUE3:
            //user handle
            break;
          case SEL6_VALUE4:
            //user handle
            break;
          case SEL6_VALUE5:
            //user handle
            break;
          case SEL6_VALUE6:
            //user handle
            break;
          case SEL6_VALUE7:
            //user handle
            break;
          case SEL6_VALUE8:
            //user handle
            break;
          case SEL6_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL7:
        currentDataPoint.valueSEL7 = dataPointPtr->valueSEL7;
        GIZWITS_LOG("Evt: EVENT_SEL7 %d\n", currentDataPoint.valueSEL7);
        switch(currentDataPoint.valueSEL7)
        {
          case SEL7_VALUE0:
            //user handle
            break;
          case SEL7_VALUE1:
            //user handle
            break;
          case SEL7_VALUE2:
            //user handle
            break;
          case SEL7_VALUE3:
            //user handle
            break;
          case SEL7_VALUE4:
            //user handle
            break;
          case SEL7_VALUE5:
            //user handle
            break;
          case SEL7_VALUE6:
            //user handle
            break;
          case SEL7_VALUE7:
            //user handle
            break;
          case SEL7_VALUE8:
            //user handle
            break;
          case SEL7_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;
      case EVENT_SEL8:
        currentDataPoint.valueSEL8 = dataPointPtr->valueSEL8;
        GIZWITS_LOG("Evt: EVENT_SEL8 %d\n", currentDataPoint.valueSEL8);
        switch(currentDataPoint.valueSEL8)
        {
          case SEL8_VALUE0:
            //user handle
            break;
          case SEL8_VALUE1:
            //user handle
            break;
          case SEL8_VALUE2:
            //user handle
            break;
          case SEL8_VALUE3:
            //user handle
            break;
          case SEL8_VALUE4:
            //user handle
            break;
          case SEL8_VALUE5:
            //user handle
            break;
          case SEL8_VALUE6:
            //user handle
            break;
          case SEL8_VALUE7:
            //user handle
            break;
          case SEL8_VALUE8:
            //user handle
            break;
          case SEL8_VALUE9:
            //user handle
            break;
          default:
            break;
        }
        break;

      case EVENT_AO1:
        currentDataPoint.valueAO1 = dataPointPtr->valueAO1;
        GIZWITS_LOG("Evt:EVENT_AO1 %4f\n",currentDataPoint.valueAO1);
        //user handle
        break;
      case EVENT_AO2:
        currentDataPoint.valueAO2 = dataPointPtr->valueAO2;
        GIZWITS_LOG("Evt:EVENT_AO2 %4f\n",currentDataPoint.valueAO2);
        //user handle
        break;
      case EVENT_AO3:
        currentDataPoint.valueAO3 = dataPointPtr->valueAO3;
        GIZWITS_LOG("Evt:EVENT_AO3 %4f\n",currentDataPoint.valueAO3);
        //user handle
        break;
      case EVENT_AO4:
        currentDataPoint.valueAO4 = dataPointPtr->valueAO4;
        GIZWITS_LOG("Evt:EVENT_AO4 %4f\n",currentDataPoint.valueAO4);
        //user handle
        break;
      case EVENT_AO5:
        currentDataPoint.valueAO5 = dataPointPtr->valueAO5;
        GIZWITS_LOG("Evt:EVENT_AO5 %4f\n",currentDataPoint.valueAO5);
        //user handle
        break;
      case EVENT_AO6:
        currentDataPoint.valueAO6 = dataPointPtr->valueAO6;
        GIZWITS_LOG("Evt:EVENT_AO6 %4f\n",currentDataPoint.valueAO6);
        //user handle
        break;
      case EVENT_AO7:
        currentDataPoint.valueAO7 = dataPointPtr->valueAO7;
        GIZWITS_LOG("Evt:EVENT_AO7 %4f\n",currentDataPoint.valueAO7);
        //user handle
        break;
      case EVENT_AO8:
        currentDataPoint.valueAO8 = dataPointPtr->valueAO8;
        GIZWITS_LOG("Evt:EVENT_AO8 %4f\n",currentDataPoint.valueAO8);
        //user handle
        break;


      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 
    currentDataPoint.valueDI1 =(P1IN&BIT0) ;//Add Sensor Data Collection
    currentDataPoint.valueDI2 =(P1IN&BIT1) ;//Add Sensor Data Collection
    currentDataPoint.valueDI3 =(P1IN&BIT2) ;//Add Sensor Data Collection
    /*currentDataPoint.valueDI4 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI5 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI6 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI7 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI8 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI9 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI10 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI11 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI12 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI13 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI14 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI15 = ;//Add Sensor Data Collection
    currentDataPoint.valueDI16 = ;//Add Sensor Data Collection*/
    currentDataPoint.valueAI1 = 30;//Add Sensor Data Collection
    currentDataPoint.valueAI2 = 40;//Add Sensor Data Collection
    /*currentDataPoint.valueAI3 = ;//Add Sensor Data Collection
    currentDataPoint.valueAI4 = ;//Add Sensor Data Collection
    currentDataPoint.valueAI5 = ;//Add Sensor Data Collection
    currentDataPoint.valueAI6 = ;//Add Sensor Data Collection
    currentDataPoint.valueAI7 = ;//Add Sensor Data Collection
    currentDataPoint.valueAI8 = ;//Add Sensor Data Collection

    */
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueDO1 = ;
      currentDataPoint.valueDO2 = ;
      currentDataPoint.valueDO3 = ;
      currentDataPoint.valueDO4 = ;
      currentDataPoint.valueDO5 = ;
      currentDataPoint.valueDO6 = ;
      currentDataPoint.valueDO7 = ;
      currentDataPoint.valueDO8 = ;
      currentDataPoint.valueDO9 = ;
      currentDataPoint.valueDO10 = ;
      currentDataPoint.valueDO11 = ;
      currentDataPoint.valueDO12 = ;
      currentDataPoint.valueDO13 = ;
      currentDataPoint.valueDO14 = ;
      currentDataPoint.valueDO15 = ;
      currentDataPoint.valueDO16 = ;
      currentDataPoint.valueSEL1 = ;
      currentDataPoint.valueSEL2 = ;
      currentDataPoint.valueSEL3 = ;
      currentDataPoint.valueSEL4 = ;
      currentDataPoint.valueSEL5 = ;
      currentDataPoint.valueSEL6 = ;
      currentDataPoint.valueSEL7 = ;
      currentDataPoint.valueSEL8 = ;
      currentDataPoint.valueAO1 = ;
      currentDataPoint.valueAO2 = ;
      currentDataPoint.valueAO3 = ;
      currentDataPoint.valueAO4 = ;
      currentDataPoint.valueAO5 = ;
      currentDataPoint.valueAO6 = ;
      currentDataPoint.valueAO7 = ;
      currentDataPoint.valueAO8 = ;
      currentDataPoint.valueDI1 = ;
      currentDataPoint.valueDI2 = ;
      currentDataPoint.valueDI3 = ;
      currentDataPoint.valueDI4 = ;
      currentDataPoint.valueDI5 = ;
      currentDataPoint.valueDI6 = ;
      currentDataPoint.valueDI7 = ;
      currentDataPoint.valueDI8 = ;
      currentDataPoint.valueDI9 = ;
      currentDataPoint.valueDI10 = ;
      currentDataPoint.valueDI11 = ;
      currentDataPoint.valueDI12 = ;
      currentDataPoint.valueDI13 = ;
      currentDataPoint.valueDI14 = ;
      currentDataPoint.valueDI15 = ;
      currentDataPoint.valueDI16 = ;
      currentDataPoint.valueAI1 = ;
      currentDataPoint.valueAI2 = ;
      currentDataPoint.valueAI3 = ;
      currentDataPoint.valueAI4 = ;
      currentDataPoint.valueAI5 = ;
      currentDataPoint.valueAI6 = ;
      currentDataPoint.valueAI7 = ;
      currentDataPoint.valueAI8 = ;
    */

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}


/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
         ((void (*)())0xFFFE)();
}

/**@} */

/**


/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }

    GIZWITS_LOG("\n");
#endif
    
    for(i=0; i<len; i++)
    {
        uart1_byte(buf[i]);
        if(i >=2 && buf[i] == 0xFF)
        {
          uart1_byte(0x55);
        }
    }
        
    return len;
}
