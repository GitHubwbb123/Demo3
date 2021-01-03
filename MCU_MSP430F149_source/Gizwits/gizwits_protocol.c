/**
************************************************************
* @file         gizwits_protocol.c
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
#include "ringBuffer.h"
#include "gizwits_product.h"
#include "dataPointTools.h"

/** Protocol global variables **/
gizwitsProtocol_t gizwitsProtocol;


/**@name The serial port receives the ring buffer implementation
* @{
*/
rb_t pRb;                                               ///< Ring buffer structure variable
static uint8_t rbBuf[RB_MAX_LEN];                       ///< Ring buffer data cache buffer


/**@} */

/**
* @brief Write data to the ring buffer
* @param [in] buf        : buf adress
* @param [in] len        : byte length
* @return   correct : Returns the length of the written data
            failure : -1
*/
int32_t gizPutData(uint8_t *buf, uint32_t len)
{
    int32_t count = 0;

    if(NULL == buf)
    {
        GIZWITS_LOG("ERR: gizPutData buf is empty \n");
        return -1;
    }

    count = rbWrite(&pRb, buf, len);
    if(count != len)
    {
        GIZWITS_LOG("ERR: Failed to rbWrite \n");
        return -1;
    }

    return count;
}



/**
* @brief Protocol header initialization
*
* @param [out] head         : Protocol header pointer
*
* @return 0， success; other， failure    
*/
static int8_t gizProtocolHeadInit(protocolHead_t *head)
{
    if(NULL == head)
    {
        GIZWITS_LOG("ERR: gizProtocolHeadInit head is empty \n");
        return -1;
    }

    memset((uint8_t *)head, 0, sizeof(protocolHead_t));
    head->head[0] = 0xFF;
    head->head[1] = 0xFF;

    return 0;
}

/**
* @brief Protocol ACK check processing function
*
* @param [in] data            : data adress
* @param [in] len             : data length
*
* @return 0， suceess; other， failure
*/
static int8_t gizProtocolWaitAck(uint8_t *gizdata, uint32_t len)
{
    if(NULL == gizdata)
    {
        GIZWITS_LOG("ERR: data is empty \n");
        return -1;
    }

    memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
    memcpy((uint8_t *)gizwitsProtocol.waitAck.buf, gizdata, len);
    gizwitsProtocol.waitAck.dataLen = (uint16_t)len;
    
    gizwitsProtocol.waitAck.flag = 1;
    gizwitsProtocol.waitAck.sendTime = gizGetTimerCount();

    return 0;
}
/**
* @brief generates "controlled events" according to protocol

* @param [in] issuedData: Controlled data
* @param [out] info: event queue
* @param [out] dataPoints: data point data
* @return 0, the implementation of success, non-0, failed
*/
static int8_t ICACHE_FLASH_ATTR gizDataPoint2Event(gizwitsIssued_t *issuedData, eventInfo_t *info, dataPoint_t *dataPoints)
{
    if((NULL == issuedData) || (NULL == info) ||(NULL == dataPoints))
    {
        GIZWITS_LOG("gizDataPoint2Event Error , Illegal Param\n");
        return -1;
    }
    
    /** Greater than 1 byte to do bit conversion **/
    if(sizeof(issuedData->attrFlags) > 1)
    {
        if(-1 == gizByteOrderExchange((uint8_t *)&issuedData->attrFlags,sizeof(attrFlags_t)))
        {
            GIZWITS_LOG("gizByteOrderExchange Error\n");
            return -1;
        }
    }
    
    if(0x01 == issuedData->attrFlags.flagDO1)
    {
        info->event[info->num] = EVENT_DO1;
        info->num++;
        dataPoints->valueDO1 = gizStandardDecompressionValue(DO1_BYTEOFFSET,DO1_BITOFFSET,DO1_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO2)
    {
        info->event[info->num] = EVENT_DO2;
        info->num++;
        dataPoints->valueDO2 = gizStandardDecompressionValue(DO2_BYTEOFFSET,DO2_BITOFFSET,DO2_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO3)
    {
        info->event[info->num] = EVENT_DO3;
        info->num++;
        dataPoints->valueDO3 = gizStandardDecompressionValue(DO3_BYTEOFFSET,DO3_BITOFFSET,DO3_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO4)
    {
        info->event[info->num] = EVENT_DO4;
        info->num++;
        dataPoints->valueDO4 = gizStandardDecompressionValue(DO4_BYTEOFFSET,DO4_BITOFFSET,DO4_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO5)
    {
        info->event[info->num] = EVENT_DO5;
        info->num++;
        dataPoints->valueDO5 = gizStandardDecompressionValue(DO5_BYTEOFFSET,DO5_BITOFFSET,DO5_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO6)
    {
        info->event[info->num] = EVENT_DO6;
        info->num++;
        dataPoints->valueDO6 = gizStandardDecompressionValue(DO6_BYTEOFFSET,DO6_BITOFFSET,DO6_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO7)
    {
        info->event[info->num] = EVENT_DO7;
        info->num++;
        dataPoints->valueDO7 = gizStandardDecompressionValue(DO7_BYTEOFFSET,DO7_BITOFFSET,DO7_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO8)
    {
        info->event[info->num] = EVENT_DO8;
        info->num++;
        dataPoints->valueDO8 = gizStandardDecompressionValue(DO8_BYTEOFFSET,DO8_BITOFFSET,DO8_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO9)
    {
        info->event[info->num] = EVENT_DO9;
        info->num++;
        dataPoints->valueDO9 = gizStandardDecompressionValue(DO9_BYTEOFFSET,DO9_BITOFFSET,DO9_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO10)
    {
        info->event[info->num] = EVENT_DO10;
        info->num++;
        dataPoints->valueDO10 = gizStandardDecompressionValue(DO10_BYTEOFFSET,DO10_BITOFFSET,DO10_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO11)
    {
        info->event[info->num] = EVENT_DO11;
        info->num++;
        dataPoints->valueDO11 = gizStandardDecompressionValue(DO11_BYTEOFFSET,DO11_BITOFFSET,DO11_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO12)
    {
        info->event[info->num] = EVENT_DO12;
        info->num++;
        dataPoints->valueDO12 = gizStandardDecompressionValue(DO12_BYTEOFFSET,DO12_BITOFFSET,DO12_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO13)
    {
        info->event[info->num] = EVENT_DO13;
        info->num++;
        dataPoints->valueDO13 = gizStandardDecompressionValue(DO13_BYTEOFFSET,DO13_BITOFFSET,DO13_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO14)
    {
        info->event[info->num] = EVENT_DO14;
        info->num++;
        dataPoints->valueDO14 = gizStandardDecompressionValue(DO14_BYTEOFFSET,DO14_BITOFFSET,DO14_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO15)
    {
        info->event[info->num] = EVENT_DO15;
        info->num++;
        dataPoints->valueDO15 = gizStandardDecompressionValue(DO15_BYTEOFFSET,DO15_BITOFFSET,DO15_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagDO16)
    {
        info->event[info->num] = EVENT_DO16;
        info->num++;
        dataPoints->valueDO16 = gizStandardDecompressionValue(DO16_BYTEOFFSET,DO16_BITOFFSET,DO16_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL1)
    {
        info->event[info->num] = EVENT_SEL1;
        info->num++;
        dataPoints->valueSEL1 = gizStandardDecompressionValue(SEL1_BYTEOFFSET,SEL1_BITOFFSET,SEL1_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL2)
    {
        info->event[info->num] = EVENT_SEL2;
        info->num++;
        dataPoints->valueSEL2 = gizStandardDecompressionValue(SEL2_BYTEOFFSET,SEL2_BITOFFSET,SEL2_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL3)
    {
        info->event[info->num] = EVENT_SEL3;
        info->num++;
        dataPoints->valueSEL3 = gizStandardDecompressionValue(SEL3_BYTEOFFSET,SEL3_BITOFFSET,SEL3_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL4)
    {
        info->event[info->num] = EVENT_SEL4;
        info->num++;
        dataPoints->valueSEL4 = gizStandardDecompressionValue(SEL4_BYTEOFFSET,SEL4_BITOFFSET,SEL4_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL5)
    {
        info->event[info->num] = EVENT_SEL5;
        info->num++;
        dataPoints->valueSEL5 = gizStandardDecompressionValue(SEL5_BYTEOFFSET,SEL5_BITOFFSET,SEL5_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL6)
    {
        info->event[info->num] = EVENT_SEL6;
        info->num++;
        dataPoints->valueSEL6 = gizStandardDecompressionValue(SEL6_BYTEOFFSET,SEL6_BITOFFSET,SEL6_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL7)
    {
        info->event[info->num] = EVENT_SEL7;
        info->num++;
        dataPoints->valueSEL7 = gizStandardDecompressionValue(SEL7_BYTEOFFSET,SEL7_BITOFFSET,SEL7_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
    if(0x01 == issuedData->attrFlags.flagSEL8)
    {
        info->event[info->num] = EVENT_SEL8;
        info->num++;
        dataPoints->valueSEL8 = gizStandardDecompressionValue(SEL8_BYTEOFFSET,SEL8_BITOFFSET,SEL8_LEN,(uint8_t *)&issuedData->attrVals.wBitBuf,sizeof(issuedData->attrVals.wBitBuf));
    }
        
        
    if(0x01 == issuedData->attrFlags.flagAO1)
    {
        info->event[info->num] = EVENT_AO1;
        info->num++;
        dataPoints->valueAO1 = gizX2YFloat(AO1_RATIO,  AO1_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO1)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO2)
    {
        info->event[info->num] = EVENT_AO2;
        info->num++;
        dataPoints->valueAO2 = gizX2YFloat(AO2_RATIO,  AO2_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO2)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO3)
    {
        info->event[info->num] = EVENT_AO3;
        info->num++;
        dataPoints->valueAO3 = gizX2YFloat(AO3_RATIO,  AO3_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO3)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO4)
    {
        info->event[info->num] = EVENT_AO4;
        info->num++;
        dataPoints->valueAO4 = gizX2YFloat(AO4_RATIO,  AO4_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO4)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO5)
    {
        info->event[info->num] = EVENT_AO5;
        info->num++;
        dataPoints->valueAO5 = gizX2YFloat(AO5_RATIO,  AO5_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO5)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO6)
    {
        info->event[info->num] = EVENT_AO6;
        info->num++;
        dataPoints->valueAO6 = gizX2YFloat(AO6_RATIO,  AO6_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO6)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO7)
    {
        info->event[info->num] = EVENT_AO7;
        info->num++;
        dataPoints->valueAO7 = gizX2YFloat(AO7_RATIO,  AO7_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO7)));
    }
        
    if(0x01 == issuedData->attrFlags.flagAO8)
    {
        info->event[info->num] = EVENT_AO8;
        info->num++;
        dataPoints->valueAO8 = gizX2YFloat(AO8_RATIO,  AO8_ADDITION, (float)(exchangeBytes(issuedData->attrVals.valueAO8)));
    }
    
    return 0;
}

/**
* @brief contrasts the current data with the last data
*
* @param [in] cur: current data point data
* @param [in] last: last data point data
*
* @return: 0, no change in data; 1, data changes
*/
static int8_t ICACHE_FLASH_ATTR gizCheckReport(dataPoint_t *cur, dataPoint_t *last)
{
    int8_t ret = 0;
    static uint32_t lastReportTime = 0;
    uint32_t currentTime = 0;

    if((NULL == cur) || (NULL == last))
    {
        GIZWITS_LOG("gizCheckReport Error , Illegal Param\n");
        return -1;
    }
    currentTime = gizGetTimerCount();
    if(last->valueDO1 != cur->valueDO1)
    {
        GIZWITS_LOG("valueDO1 Changed\n");
        ret = 1;
    }
    if(last->valueDO2 != cur->valueDO2)
    {
        GIZWITS_LOG("valueDO2 Changed\n");
        ret = 1;
    }
    if(last->valueDO3 != cur->valueDO3)
    {
        GIZWITS_LOG("valueDO3 Changed\n");
        ret = 1;
    }
    if(last->valueDO4 != cur->valueDO4)
    {
        GIZWITS_LOG("valueDO4 Changed\n");
        ret = 1;
    }
    if(last->valueDO5 != cur->valueDO5)
    {
        GIZWITS_LOG("valueDO5 Changed\n");
        ret = 1;
    }
    if(last->valueDO6 != cur->valueDO6)
    {
        GIZWITS_LOG("valueDO6 Changed\n");
        ret = 1;
    }
    if(last->valueDO7 != cur->valueDO7)
    {
        GIZWITS_LOG("valueDO7 Changed\n");
        ret = 1;
    }
    if(last->valueDO8 != cur->valueDO8)
    {
        GIZWITS_LOG("valueDO8 Changed\n");
        ret = 1;
    }
    if(last->valueDO9 != cur->valueDO9)
    {
        GIZWITS_LOG("valueDO9 Changed\n");
        ret = 1;
    }
    if(last->valueDO10 != cur->valueDO10)
    {
        GIZWITS_LOG("valueDO10 Changed\n");
        ret = 1;
    }
    if(last->valueDO11 != cur->valueDO11)
    {
        GIZWITS_LOG("valueDO11 Changed\n");
        ret = 1;
    }
    if(last->valueDO12 != cur->valueDO12)
    {
        GIZWITS_LOG("valueDO12 Changed\n");
        ret = 1;
    }
    if(last->valueDO13 != cur->valueDO13)
    {
        GIZWITS_LOG("valueDO13 Changed\n");
        ret = 1;
    }
    if(last->valueDO14 != cur->valueDO14)
    {
        GIZWITS_LOG("valueDO14 Changed\n");
        ret = 1;
    }
    if(last->valueDO15 != cur->valueDO15)
    {
        GIZWITS_LOG("valueDO15 Changed\n");
        ret = 1;
    }
    if(last->valueDO16 != cur->valueDO16)
    {
        GIZWITS_LOG("valueDO16 Changed\n");
        ret = 1;
    }
    if(last->valueSEL1 != cur->valueSEL1)
    {
        GIZWITS_LOG("valueSEL1 Changed\n");
        ret = 1;
    }
    if(last->valueSEL2 != cur->valueSEL2)
    {
        GIZWITS_LOG("valueSEL2 Changed\n");
        ret = 1;
    }
    if(last->valueSEL3 != cur->valueSEL3)
    {
        GIZWITS_LOG("valueSEL3 Changed\n");
        ret = 1;
    }
    if(last->valueSEL4 != cur->valueSEL4)
    {
        GIZWITS_LOG("valueSEL4 Changed\n");
        ret = 1;
    }
    if(last->valueSEL5 != cur->valueSEL5)
    {
        GIZWITS_LOG("valueSEL5 Changed\n");
        ret = 1;
    }
    if(last->valueSEL6 != cur->valueSEL6)
    {
        GIZWITS_LOG("valueSEL6 Changed\n");
        ret = 1;
    }
    if(last->valueSEL7 != cur->valueSEL7)
    {
        GIZWITS_LOG("valueSEL7 Changed\n");
        ret = 1;
    }
    if(last->valueSEL8 != cur->valueSEL8)
    {
        GIZWITS_LOG("valueSEL8 Changed\n");
        ret = 1;
    }
    if(last->valueAO1 != cur->valueAO1)
    {
        GIZWITS_LOG("valueAO1 Changed\n");
        ret = 1;
    }
    if(last->valueAO2 != cur->valueAO2)
    {
        GIZWITS_LOG("valueAO2 Changed\n");
        ret = 1;
    }
    if(last->valueAO3 != cur->valueAO3)
    {
        GIZWITS_LOG("valueAO3 Changed\n");
        ret = 1;
    }
    if(last->valueAO4 != cur->valueAO4)
    {
        GIZWITS_LOG("valueAO4 Changed\n");
        ret = 1;
    }
    if(last->valueAO5 != cur->valueAO5)
    {
        GIZWITS_LOG("valueAO5 Changed\n");
        ret = 1;
    }
    if(last->valueAO6 != cur->valueAO6)
    {
        GIZWITS_LOG("valueAO6 Changed\n");
        ret = 1;
    }
    if(last->valueAO7 != cur->valueAO7)
    {
        GIZWITS_LOG("valueAO7 Changed\n");
        ret = 1;
    }
    if(last->valueAO8 != cur->valueAO8)
    {
        GIZWITS_LOG("valueAO8 Changed\n");
        ret = 1;
    }
    if(last->valueDI1 != cur->valueDI1)
    {
        GIZWITS_LOG("valueDI1 Changed\n");
        ret = 1;
    }
    if(last->valueDI2 != cur->valueDI2)
    {
        GIZWITS_LOG("valueDI2 Changed\n");
        ret = 1;
    }
    if(last->valueDI3 != cur->valueDI3)
    {
        GIZWITS_LOG("valueDI3 Changed\n");
        ret = 1;
    }
    if(last->valueDI4 != cur->valueDI4)
    {
        GIZWITS_LOG("valueDI4 Changed\n");
        ret = 1;
    }
    if(last->valueDI5 != cur->valueDI5)
    {
        GIZWITS_LOG("valueDI5 Changed\n");
        ret = 1;
    }
    if(last->valueDI6 != cur->valueDI6)
    {
        GIZWITS_LOG("valueDI6 Changed\n");
        ret = 1;
    }
    if(last->valueDI7 != cur->valueDI7)
    {
        GIZWITS_LOG("valueDI7 Changed\n");
        ret = 1;
    }
    if(last->valueDI8 != cur->valueDI8)
    {
        GIZWITS_LOG("valueDI8 Changed\n");
        ret = 1;
    }
    if(last->valueDI9 != cur->valueDI9)
    {
        GIZWITS_LOG("valueDI9 Changed\n");
        ret = 1;
    }
    if(last->valueDI10 != cur->valueDI10)
    {
        GIZWITS_LOG("valueDI10 Changed\n");
        ret = 1;
    }
    if(last->valueDI11 != cur->valueDI11)
    {
        GIZWITS_LOG("valueDI11 Changed\n");
        ret = 1;
    }
    if(last->valueDI12 != cur->valueDI12)
    {
        GIZWITS_LOG("valueDI12 Changed\n");
        ret = 1;
    }
    if(last->valueDI13 != cur->valueDI13)
    {
        GIZWITS_LOG("valueDI13 Changed\n");
        ret = 1;
    }
    if(last->valueDI14 != cur->valueDI14)
    {
        GIZWITS_LOG("valueDI14 Changed\n");
        ret = 1;
    }
    if(last->valueDI15 != cur->valueDI15)
    {
        GIZWITS_LOG("valueDI15 Changed\n");
        ret = 1;
    }
    if(last->valueDI16 != cur->valueDI16)
    {
        GIZWITS_LOG("valueDI16 Changed\n");
        ret = 1;
    }

    if(last->valueAI1 != cur->valueAI1)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI1 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI2 != cur->valueAI2)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI2 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI3 != cur->valueAI3)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI3 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI4 != cur->valueAI4)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI4 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI5 != cur->valueAI5)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI5 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI6 != cur->valueAI6)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI6 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI7 != cur->valueAI7)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI7 Changed\n");
            ret = 1;
        }
    }
    if(last->valueAI8 != cur->valueAI8)
    {
        if(currentTime - lastReportTime >= REPORT_TIME_MAX)
        {
            GIZWITS_LOG("valueAI8 Changed\n");
            ret = 1;
        }
    }

    if(1 == ret)
    {
        lastReportTime = gizGetTimerCount();
    }
    return ret;
}

/**
* @brief User data point data is converted to wit the cloud to report data point data
*
* @param [in] dataPoints: user data point data address
* @param [out] devStatusPtr: wit the cloud data point data address
*
* @return 0, the correct return; -1, the error returned
*/
static int8_t ICACHE_FLASH_ATTR gizDataPoints2ReportData(dataPoint_t *dataPoints , devStatus_t *devStatusPtr)
{
    if((NULL == dataPoints) || (NULL == devStatusPtr))
    {
        GIZWITS_LOG("gizDataPoints2ReportData Error , Illegal Param\n");
        return -1;
    }

    gizMemset((uint8_t *)devStatusPtr->wBitBuf,0,sizeof(devStatusPtr->wBitBuf));
    gizMemset((uint8_t *)devStatusPtr->rBitBuf,0,sizeof(devStatusPtr->rBitBuf));

    gizStandardCompressValue(DO1_BYTEOFFSET,DO1_BITOFFSET,DO1_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO1);
    gizStandardCompressValue(DO2_BYTEOFFSET,DO2_BITOFFSET,DO2_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO2);
    gizStandardCompressValue(DO3_BYTEOFFSET,DO3_BITOFFSET,DO3_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO3);
    gizStandardCompressValue(DO4_BYTEOFFSET,DO4_BITOFFSET,DO4_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO4);
    gizStandardCompressValue(DO5_BYTEOFFSET,DO5_BITOFFSET,DO5_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO5);
    gizStandardCompressValue(DO6_BYTEOFFSET,DO6_BITOFFSET,DO6_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO6);
    gizStandardCompressValue(DO7_BYTEOFFSET,DO7_BITOFFSET,DO7_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO7);
    gizStandardCompressValue(DO8_BYTEOFFSET,DO8_BITOFFSET,DO8_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO8);
    gizStandardCompressValue(DO9_BYTEOFFSET,DO9_BITOFFSET,DO9_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO9);
    gizStandardCompressValue(DO10_BYTEOFFSET,DO10_BITOFFSET,DO10_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO10);
    gizStandardCompressValue(DO11_BYTEOFFSET,DO11_BITOFFSET,DO11_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO11);
    gizStandardCompressValue(DO12_BYTEOFFSET,DO12_BITOFFSET,DO12_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO12);
    gizStandardCompressValue(DO13_BYTEOFFSET,DO13_BITOFFSET,DO13_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO13);
    gizStandardCompressValue(DO14_BYTEOFFSET,DO14_BITOFFSET,DO14_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO14);
    gizStandardCompressValue(DO15_BYTEOFFSET,DO15_BITOFFSET,DO15_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO15);
    gizStandardCompressValue(DO16_BYTEOFFSET,DO16_BITOFFSET,DO16_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDO16);
    if(dataPoints->valueSEL1 >= SEL1_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL1 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL1_BYTEOFFSET,SEL1_BITOFFSET,SEL1_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL1);  
    }
    if(dataPoints->valueSEL2 >= SEL2_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL2 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL2_BYTEOFFSET,SEL2_BITOFFSET,SEL2_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL2);  
    }
    if(dataPoints->valueSEL3 >= SEL3_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL3 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL3_BYTEOFFSET,SEL3_BITOFFSET,SEL3_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL3);  
    }
    if(dataPoints->valueSEL4 >= SEL4_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL4 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL4_BYTEOFFSET,SEL4_BITOFFSET,SEL4_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL4);  
    }
    if(dataPoints->valueSEL5 >= SEL5_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL5 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL5_BYTEOFFSET,SEL5_BITOFFSET,SEL5_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL5);  
    }
    if(dataPoints->valueSEL6 >= SEL6_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL6 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL6_BYTEOFFSET,SEL6_BITOFFSET,SEL6_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL6);  
    }
    if(dataPoints->valueSEL7 >= SEL7_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL7 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL7_BYTEOFFSET,SEL7_BITOFFSET,SEL7_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL7);  
    }
    if(dataPoints->valueSEL8 >= SEL8_VALUE_MAX)
    {
        GIZWITS_LOG("[ERROR] valueSEL8 Error , Illegal Overstep\n");
        return -1;
    }
    else
    {
        gizStandardCompressValue(SEL8_BYTEOFFSET,SEL8_BITOFFSET,SEL8_LEN,(uint8_t *)devStatusPtr,dataPoints->valueSEL8);  
    }
    gizStandardCompressValue(DI1_BYTEOFFSET,DI1_BITOFFSET,DI1_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI1);
    gizStandardCompressValue(DI2_BYTEOFFSET,DI2_BITOFFSET,DI2_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI2);
    gizStandardCompressValue(DI3_BYTEOFFSET,DI3_BITOFFSET,DI3_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI3);
    gizStandardCompressValue(DI4_BYTEOFFSET,DI4_BITOFFSET,DI4_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI4);
    gizStandardCompressValue(DI5_BYTEOFFSET,DI5_BITOFFSET,DI5_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI5);
    gizStandardCompressValue(DI6_BYTEOFFSET,DI6_BITOFFSET,DI6_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI6);
    gizStandardCompressValue(DI7_BYTEOFFSET,DI7_BITOFFSET,DI7_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI7);
    gizStandardCompressValue(DI8_BYTEOFFSET,DI8_BITOFFSET,DI8_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI8);
    gizStandardCompressValue(DI9_BYTEOFFSET,DI9_BITOFFSET,DI9_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI9);
    gizStandardCompressValue(DI10_BYTEOFFSET,DI10_BITOFFSET,DI10_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI10);
    gizStandardCompressValue(DI11_BYTEOFFSET,DI11_BITOFFSET,DI11_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI11);
    gizStandardCompressValue(DI12_BYTEOFFSET,DI12_BITOFFSET,DI12_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI12);
    gizStandardCompressValue(DI13_BYTEOFFSET,DI13_BITOFFSET,DI13_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI13);
    gizStandardCompressValue(DI14_BYTEOFFSET,DI14_BITOFFSET,DI14_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI14);
    gizStandardCompressValue(DI15_BYTEOFFSET,DI15_BITOFFSET,DI15_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI15);
    gizStandardCompressValue(DI16_BYTEOFFSET,DI16_BITOFFSET,DI16_LEN,(uint8_t *)devStatusPtr,dataPoints->valueDI16);
    gizByteOrderExchange((uint8_t *)devStatusPtr->wBitBuf,sizeof(devStatusPtr->wBitBuf));
    gizByteOrderExchange((uint8_t *)devStatusPtr->rBitBuf,sizeof(devStatusPtr->rBitBuf));


    devStatusPtr->valueAO1 = exchangeBytes(gizY2XFloat(AO1_RATIO,  AO1_ADDITION, dataPoints->valueAO1));     
    devStatusPtr->valueAO2 = exchangeBytes(gizY2XFloat(AO2_RATIO,  AO2_ADDITION, dataPoints->valueAO2));     
    devStatusPtr->valueAO3 = exchangeBytes(gizY2XFloat(AO3_RATIO,  AO3_ADDITION, dataPoints->valueAO3));     
    devStatusPtr->valueAO4 = exchangeBytes(gizY2XFloat(AO4_RATIO,  AO4_ADDITION, dataPoints->valueAO4));     
    devStatusPtr->valueAO5 = exchangeBytes(gizY2XFloat(AO5_RATIO,  AO5_ADDITION, dataPoints->valueAO5));     
    devStatusPtr->valueAO6 = exchangeBytes(gizY2XFloat(AO6_RATIO,  AO6_ADDITION, dataPoints->valueAO6));     
    devStatusPtr->valueAO7 = exchangeBytes(gizY2XFloat(AO7_RATIO,  AO7_ADDITION, dataPoints->valueAO7));     
    devStatusPtr->valueAO8 = exchangeBytes(gizY2XFloat(AO8_RATIO,  AO8_ADDITION, dataPoints->valueAO8));     
    devStatusPtr->valueAI1 = exchangeBytes(gizY2XFloat(AI1_RATIO,  AI1_ADDITION, dataPoints->valueAI1));     
    devStatusPtr->valueAI2 = exchangeBytes(gizY2XFloat(AI2_RATIO,  AI2_ADDITION, dataPoints->valueAI2));     
    devStatusPtr->valueAI3 = exchangeBytes(gizY2XFloat(AI3_RATIO,  AI3_ADDITION, dataPoints->valueAI3));     
    devStatusPtr->valueAI4 = exchangeBytes(gizY2XFloat(AI4_RATIO,  AI4_ADDITION, dataPoints->valueAI4));     
    devStatusPtr->valueAI5 = exchangeBytes(gizY2XFloat(AI5_RATIO,  AI5_ADDITION, dataPoints->valueAI5));     
    devStatusPtr->valueAI6 = exchangeBytes(gizY2XFloat(AI6_RATIO,  AI6_ADDITION, dataPoints->valueAI6));     
    devStatusPtr->valueAI7 = exchangeBytes(gizY2XFloat(AI7_RATIO,  AI7_ADDITION, dataPoints->valueAI7));     
    devStatusPtr->valueAI8 = exchangeBytes(gizY2XFloat(AI8_RATIO,  AI8_ADDITION, dataPoints->valueAI8));     



    return 0;
}


/**
* @brief This function is called by the Gagent module to receive the relevant protocol data from the cloud or APP
* @param [in] inData The protocol data entered
* @param [in] inLen Enter the length of the data
* @param [out] outData The output of the protocol data
* @param [out] outLen The length of the output data
* @return 0, the implementation of success, non-0, failed
*/
static int8_t gizProtocolIssuedProcess(char *did, uint8_t *inData, uint32_t inLen, uint8_t *outData, uint32_t *outLen)
{
    uint8_t issuedAction = inData[0];

    if((NULL == inData)||(NULL == outData)||(NULL == outLen))
    {
        GIZWITS_LOG("gizProtocolIssuedProcess Error , Illegal Param\n");
        return -1;
    }
    
    if(NULL == did)
    {
        memset((uint8_t *)&gizwitsProtocol.issuedProcessEvent, 0, sizeof(eventInfo_t));
        switch(issuedAction)
        {
            case ACTION_CONTROL_DEVICE:
                gizDataPoint2Event((gizwitsIssued_t *)&inData[1], &gizwitsProtocol.issuedProcessEvent,&gizwitsProtocol.gizCurrentDataPoint);
                gizwitsProtocol.issuedFlag = ACTION_CONTROL_TYPE;
                outData = NULL;
                *outLen = 0;
                break;
            
            case ACTION_READ_DEV_STATUS:
                if(0 == gizDataPoints2ReportData(&gizwitsProtocol.gizLastDataPoint,&gizwitsProtocol.reportData.devStatus))
                {
                    memcpy(outData+1, (uint8_t *)&gizwitsProtocol.reportData.devStatus, sizeof(gizwitsReport_t));
                    outData[0] = ACTION_READ_DEV_STATUS_ACK;
                    *outLen = sizeof(gizwitsReport_t)+1;
                }
                else
                {
                    return -1;
                }
                break;
            case ACTION_W2D_TRANSPARENT_DATA:
                memcpy(gizwitsProtocol.transparentBuff, &inData[1], inLen-1);
                gizwitsProtocol.transparentLen = inLen - 1;
                
                gizwitsProtocol.issuedProcessEvent.event[gizwitsProtocol.issuedProcessEvent.num] = TRANSPARENT_DATA;
                gizwitsProtocol.issuedProcessEvent.num++;
                gizwitsProtocol.issuedFlag = ACTION_W2D_TRANSPARENT_TYPE;
                outData = NULL;
                *outLen = 0;
                break;
            
                default:
                    break;
        }
    }

    return 0;
}
/**
* @brief The protocol sends data back , P0 ACK
*
* @param [in] head                  : Protocol head pointer
* @param [in] data                  : Payload data 
* @param [in] len                   : Payload data length
* @param [in] proFlag               : DID flag ,1 for Virtual sub device did ,0 for single product or gateway 
*
* @return : 0,Ack success;
*           -1，Input Param Illegal
*           -2，Serial send faild
*/
static int32_t gizProtocolIssuedDataAck(protocolHead_t *head, uint8_t *gizdata, uint32_t len, uint8_t proFlag)
{
    int32_t ret = 0;
    uint8_t tx_buf[RB_MAX_LEN];
    uint32_t offset = 0;
    uint8_t sDidLen = 0;
    uint16_t data_len = 0;
	uint8_t *pTxBuf = tx_buf;
    if(NULL == gizdata)
    {
        GIZWITS_LOG("[ERR]  data Is Null \n");
        return -1;
    }
    

    if(0x1 == proFlag)
    {
        sDidLen = *((uint8_t *)head + sizeof(protocolHead_t));
        data_len = 5 + 1 + sDidLen + len;   
    }
    else
    {
        data_len = 5 + len;
    }
    GIZWITS_LOG("len = %d , sDidLen = %d ,data_len = %d\n", len,sDidLen,data_len);
    *pTxBuf ++= 0xFF;
    *pTxBuf ++= 0xFF;
    *pTxBuf ++= (uint8_t)(data_len>>8);
    *pTxBuf ++= (uint8_t)(data_len);
    *pTxBuf ++= head->cmd + 1;
    *pTxBuf ++= head->sn;
    *pTxBuf ++= 0x00;
    *pTxBuf ++= proFlag;
    offset = 8;
    if(0x1 == proFlag)
    {
        *pTxBuf ++= sDidLen;
        offset += 1;
        memcpy(&tx_buf[offset],(uint8_t *)head+sizeof(protocolHead_t)+1,sDidLen);
        offset += sDidLen;
        pTxBuf += sDidLen;

    }
    if(0 != len)
    {
        memcpy(&tx_buf[offset],gizdata,len);
    }
    tx_buf[data_len + 4 - 1 ] = gizProtocolSum( tx_buf , (data_len+4));

    ret = uartWrite(tx_buf, data_len+4);
    if(ret < 0)
    {
        GIZWITS_LOG("uart write error %d \n", ret);
        return -2;
    }

    return 0;
}

/**
* @brief Report data interface
*
* @param [in] action            : PO action
* @param [in] data              : Payload data
* @param [in] len               : Payload data length
*
* @return : 0,Ack success;
*           -1，Input Param Illegal
*           -2，Serial send faild
*/
static int32_t gizReportData(uint8_t action, uint8_t *gizdata, uint32_t len)
{
    int32_t ret = 0;
    protocolReport_t protocolReport;

    if(NULL == gizdata)
    {
        GIZWITS_LOG("gizReportData Error , Illegal Param\n");
        return -1;
    }
    gizProtocolHeadInit((protocolHead_t *)&protocolReport);
    protocolReport.head.cmd = CMD_REPORT_P0;
    protocolReport.head.sn = gizwitsProtocol.sn++;
    protocolReport.action = action;
    protocolReport.head.len = exchangeBytes(sizeof(protocolReport_t)-4);
    memcpy((gizwitsReport_t *)&protocolReport.reportData, (gizwitsReport_t *)gizdata,len);
    protocolReport.sum = gizProtocolSum((uint8_t *)&protocolReport, sizeof(protocolReport_t));
    
    ret = uartWrite((uint8_t *)&protocolReport, sizeof(protocolReport_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
        return -2;
    }

    gizProtocolWaitAck((uint8_t *)&protocolReport, sizeof(protocolReport_t));

    return ret;
}/**
* @brief Datapoints reporting mechanism
*
* 1. Changes are reported immediately

* 2. Data timing report , 600000 Millisecond
* 
*@param [in] currentData       : Current datapoints value
* @return : NULL
*/
static void gizDevReportPolicy(dataPoint_t *currentData)
{
    static uint32_t lastRepTime = 0;
    uint32_t timeNow = gizGetTimerCount();

    if((1 == gizCheckReport(currentData, (dataPoint_t *)&gizwitsProtocol.gizLastDataPoint)))
    {
        GIZWITS_LOG("changed, report data\n");
        if(0 == gizDataPoints2ReportData(currentData,&gizwitsProtocol.reportData.devStatus))
        {
            gizReportData(ACTION_REPORT_DEV_STATUS, (uint8_t *)&gizwitsProtocol.reportData.devStatus, sizeof(devStatus_t));        }       
        memcpy((uint8_t *)&gizwitsProtocol.gizLastDataPoint, (uint8_t *)currentData, sizeof(dataPoint_t));
    }

    if((0 == (timeNow % (600000))) && (lastRepTime != timeNow))
    {
        GIZWITS_LOG("Info: 600S report data\n");
        if(0 == gizDataPoints2ReportData(currentData,&gizwitsProtocol.reportData.devStatus))
        {
            gizReportData(ACTION_REPORT_DEV_STATUS, (uint8_t *)&gizwitsProtocol.reportData.devStatus, sizeof(devStatus_t));
        }       
        memcpy((uint8_t *)&gizwitsProtocol.gizLastDataPoint, (uint8_t *)currentData, sizeof(dataPoint_t));

        lastRepTime = timeNow;
    }
}

/**
* @brief Get a packet of data from the ring buffer
*
* @param [in]  rb                  : Input data address
* @param [out] data                : Output data address
* @param [out] len                 : Output data length
*
* @return : 0,Return correct ;-1，Return failure;-2，Data check failure
*/
static int8_t gizProtocolGetOnePacket(rb_t *rb, uint8_t *gizdata, uint16_t *len)
{
    int32_t ret = 0;
    uint8_t sum = 0;
    int32_t i = 0;
    uint8_t tmpData;
    uint8_t tmpLen = 0;
    uint16_t tmpCount = 0;
    static uint8_t protocolFlag = 0;
    static uint16_t protocolCount = 0;
    static uint8_t lastData = 0;
    static uint8_t debugCount = 0;
    uint8_t *protocolBuff = gizdata;
    protocolHead_t *head = NULL;

    if((NULL == rb) || (NULL == gizdata) ||(NULL == len))
    {
        GIZWITS_LOG("gizProtocolGetOnePacket Error , Illegal Param\n");
        return -1;
    }

    tmpLen = rbCanRead(rb);
    if(0 == tmpLen)
    {
        return -1;
    }

    for(i=0; i<tmpLen; i++)
    {
        ret = rbRead(rb, &tmpData, 1);
        if(0 != ret)
        {
            if((0xFF == lastData) && (0xFF == tmpData))
            {
                if(0 == protocolFlag)
                {
                    protocolBuff[0] = 0xFF;
                    protocolBuff[1] = 0xFF;
                    protocolCount = 2;
                    protocolFlag = 1;
                }
                else
                {
                    if((protocolCount > 4) && (protocolCount != tmpCount))
                    {
                        protocolBuff[0] = 0xFF;
                        protocolBuff[1] = 0xFF;
                        protocolCount = 2;
                    }
                }
            }
            else if((0xFF == lastData) && (0x55 == tmpData))
            {
            }
            else
            {
                if(1 == protocolFlag)
                {
                    protocolBuff[protocolCount] = tmpData;
                    protocolCount++;

                    if(protocolCount > 4)
                    {
                        head = (protocolHead_t *)protocolBuff;
                        tmpCount = exchangeBytes(head->len)+4;
                        if(protocolCount == tmpCount)
                        {
                            break;
                        }
                    }
                }
            }

            lastData = tmpData;
            debugCount++;
        }
    }

    if((protocolCount > 4) && (protocolCount == tmpCount))
    {
        sum = gizProtocolSum(protocolBuff, protocolCount);

        if(protocolBuff[protocolCount-1] == sum)
        {
            memcpy(gizdata, protocolBuff, tmpCount);
            *len = tmpCount;
            protocolFlag = 0;

            protocolCount = 0;
            debugCount = 0;
            lastData = 0;

            return 0;
        }
        else
        {
            return -2;
        }
    }

    return 1;
}



/**
* @brief Protocol data resend

* The protocol data resend when check timeout and meet the resend limiting

* @param none    
*
* @return none
*/
static void gizProtocolResendData(void)
{
    int32_t ret = 0;

    if(0 == gizwitsProtocol.waitAck.flag)
    {
        return;
    }

    GIZWITS_LOG("Warning: timeout, resend data \n");
    
    ret = uartWrite(gizwitsProtocol.waitAck.buf, gizwitsProtocol.waitAck.dataLen);
    if(ret != gizwitsProtocol.waitAck.dataLen)
    {
        GIZWITS_LOG("ERR: resend data error\n");
    }

    gizwitsProtocol.waitAck.sendTime = gizGetTimerCount();
}

/**
* @brief Clear the ACK protocol message
*
* @param [in] head : Protocol header address
*
* @return 0， success; other， failure
*/
static int8_t gizProtocolWaitAckCheck(protocolHead_t *head)
{
    protocolHead_t *waitAckHead = (protocolHead_t *)gizwitsProtocol.waitAck.buf;

    if(NULL == head)
    {
        GIZWITS_LOG("ERR: data is empty \n");
        return -1;
    }

    if(waitAckHead->cmd+1 == head->cmd)
    {
        memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
    }

    return 0;
}

/**
* @brief Send general protocol message data
* 
* @param [in] head              : Protocol header address
*
* @return : Return effective data length;-1，return failure
*/
static int32_t gizProtocolCommonAck(protocolHead_t *head)
{
    int32_t ret = 0;
    protocolCommon_t ack;

    if(NULL == head)
    {
        GIZWITS_LOG("ERR: gizProtocolCommonAck data is empty \n");
        return -1;
    }
    memcpy((uint8_t *)&ack, (uint8_t *)head, sizeof(protocolHead_t));
    ack.head.cmd = ack.head.cmd+1;
    ack.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
    ack.sum = gizProtocolSum((uint8_t *)&ack, sizeof(protocolCommon_t));

    ret = uartWrite((uint8_t *)&ack, sizeof(protocolCommon_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    return ret;
}

/**
* @brief ACK processing function

* Time-out 200ms no ACK resend，resend two times at most

* @param none 
*
* @return none
*/
static void gizProtocolAckHandle(void)
{
    if(1 == gizwitsProtocol.waitAck.flag)
    {
        if(SEND_MAX_NUM > gizwitsProtocol.waitAck.num)
        {
            // Time-out no ACK resend
            if(SEND_MAX_TIME < (gizGetTimerCount() - gizwitsProtocol.waitAck.sendTime))
            {
                GIZWITS_LOG("Warning:gizProtocolResendData %d %d %d\n", gizGetTimerCount(), gizwitsProtocol.waitAck.sendTime, gizwitsProtocol.waitAck.num);
                gizProtocolResendData();
                gizwitsProtocol.waitAck.num++;
            }
        }
        else
        {
            memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
        }
    }
}

/**
* @brief Protocol 4.1 WiFi module requests device information
*
* @param[in] head : Protocol header address
*
* @return Return effective data length;-1，return failure
*/
static int32_t gizProtocolGetDeviceInfo(protocolHead_t * head)
{
    int32_t ret = 0;
    protocolDeviceInfo_t deviceInfo;

    if(NULL == head)
    {
        GIZWITS_LOG("gizProtocolGetDeviceInfo Error , Illegal Param\n");
        return -1;
    }

    gizProtocolHeadInit((protocolHead_t *)&deviceInfo);
    deviceInfo.head.cmd = ACK_GET_DEVICE_INFO;
    deviceInfo.head.sn = head->sn;
    memcpy((uint8_t *)deviceInfo.protocolVer, protocol_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.p0Ver, P0_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.softVer, SOFTWARE_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.hardVer, HARDWARE_VERSION, 8);
    memcpy((uint8_t *)deviceInfo.productKey, PRODUCT_KEY, strlen(PRODUCT_KEY));
    memcpy((uint8_t *)deviceInfo.productSecret, PRODUCT_SECRET, strlen(PRODUCT_SECRET));
    memset((uint8_t *)deviceInfo.devAttr, 0, 8);
    deviceInfo.devAttr[7] |= DEV_IS_GATEWAY<<0;
    deviceInfo.devAttr[7] |= (0x01<<1);
    deviceInfo.ninableTime = exchangeBytes(NINABLETIME);
    deviceInfo.head.len = exchangeBytes(sizeof(protocolDeviceInfo_t)-4);
    deviceInfo.sum = gizProtocolSum((uint8_t *)&deviceInfo, sizeof(protocolDeviceInfo_t));

    ret = uartWrite((uint8_t *)&deviceInfo, sizeof(protocolDeviceInfo_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }
    
    return ret;
}

/**
* @brief Protocol 4.7 Handling of illegal message notification

* @param[in] head  : Protocol header address
* @param[in] errno : Illegal message notification type
* @return 0， success; other， failure
*/
static int32_t gizProtocolErrorCmd(protocolHead_t *head,errorPacketsType_t errno)
{
    int32_t ret = 0;
    protocolErrorType_t errorType;

    if(NULL == head)
    {
        GIZWITS_LOG("gizProtocolErrorCmd Error , Illegal Param\n");
        return -1;
    }
    gizProtocolHeadInit((protocolHead_t *)&errorType);
    errorType.head.cmd = ACK_ERROR_PACKAGE;
    errorType.head.sn = head->sn;
    
    errorType.head.len = exchangeBytes(sizeof(protocolErrorType_t)-4);
    errorType.error = errno;
    errorType.sum = gizProtocolSum((uint8_t *)&errorType, sizeof(protocolErrorType_t));
    
    ret = uartWrite((uint8_t *)&errorType, sizeof(protocolErrorType_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    return ret;
}

/**
* @brief Protocol 4.13 Get and process network time
*
* @param [in] head : Protocol header address
*
* @return 0， success; other， failure
*/
static int8_t gizProtocolNTP(protocolHead_t *head)
{  
    protocolUTT_t *UTTInfo = (protocolUTT_t *)head;
    
    if(NULL == head)
    {
        GIZWITS_LOG("ERR: NTP is empty \n");
        return -1;
    }
    
    memcpy((uint8_t *)&gizwitsProtocol.TimeNTP,(uint8_t *)UTTInfo->time, (7 + 4));
    gizwitsProtocol.TimeNTP.year = exchangeBytes(gizwitsProtocol.TimeNTP.year);
    gizwitsProtocol.TimeNTP.ntp =exchangeWord(gizwitsProtocol.TimeNTP.ntp);

    gizwitsProtocol.NTPEvent.event[gizwitsProtocol.NTPEvent.num] = WIFI_NTP;
    gizwitsProtocol.NTPEvent.num++;
    
    gizwitsProtocol.issuedFlag = GET_NTP_TYPE;
    
    
    return 0;
}

/**
* @brief Protocol 4.4 Device MCU restarts function

* @param none
* @return none
*/
static void gizProtocolReboot(void)
{
    uint32_t timeDelay = gizGetTimerCount();
    
    /*Wait 600ms*/
    while((gizGetTimerCount() - timeDelay) <= 600);
    mcuRestart();
}

/**
* @brief Protocol 4.5 :The WiFi module informs the device MCU of working status about the WiFi module

* @param[in] status WiFi module working status
* @return none
*/
static int8_t gizProtocolModuleStatus(protocolWifiStatus_t *status)
{
    static wifiStatus_t lastStatus;

    if(NULL == status)
    {
        GIZWITS_LOG("gizProtocolModuleStatus Error , Illegal Param\n");
        return -1;
    }

    status->ststus.value = exchangeBytes(status->ststus.value);
   
    //OnBoarding mode status
    if(lastStatus.types.onboarding != status->ststus.types.onboarding)
    {
        if(1 == status->ststus.types.onboarding)
        {
            if(1 == status->ststus.types.softap)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_SOFTAP;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: SoftAP or Web mode\n");
            }

            if(1 == status->ststus.types.station)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_AIRLINK;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: AirLink mode\n");
            }
        }
        else
        {
            if(1 == status->ststus.types.softap)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_SOFTAP;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: SoftAP or Web mode\n");
            }

            if(1 == status->ststus.types.station)
            {
                gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_STATION;
                gizwitsProtocol.wifiStatusEvent.num++;
                GIZWITS_LOG("OnBoarding: Station mode\n");
            }
        }
    }

    //binding mode status
    if(lastStatus.types.binding != status->ststus.types.binding)
    {
        lastStatus.types.binding = status->ststus.types.binding;
        if(1 == status->ststus.types.binding)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_OPEN_BINDING;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: in binding mode\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CLOSE_BINDING;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: out binding mode\n");
        }
    }

    //router status
    if(lastStatus.types.con_route != status->ststus.types.con_route)
    {
        lastStatus.types.con_route = status->ststus.types.con_route;
        if(1 == status->ststus.types.con_route)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_ROUTER;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: connected router\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_ROUTER;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: disconnected router\n");
        }
    }

    //M2M server status
    if(lastStatus.types.con_m2m != status->ststus.types.con_m2m)
    {
        lastStatus.types.con_m2m = status->ststus.types.con_m2m;
        if(1 == status->ststus.types.con_m2m)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_M2M;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: connected m2m\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_M2M;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: disconnected m2m\n");
        }
    }

    //APP status
    if(lastStatus.types.app != status->ststus.types.app)
    {
        lastStatus.types.app = status->ststus.types.app;
        if(1 == status->ststus.types.app)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CON_APP;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: app connect\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_DISCON_APP;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: no app connect\n");
        }
    }

    //test mode status
    if(lastStatus.types.test != status->ststus.types.test)
    {
        lastStatus.types.test = status->ststus.types.test;
        if(1 == status->ststus.types.test)
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_OPEN_TESTMODE;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: in test mode\n");
        }
        else
        {
            gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_CLOSE_TESTMODE;
            gizwitsProtocol.wifiStatusEvent.num++;
            GIZWITS_LOG("WiFi status: out test mode\n");
        }
    }

    gizwitsProtocol.wifiStatusEvent.event[gizwitsProtocol.wifiStatusEvent.num] = WIFI_RSSI;
    gizwitsProtocol.wifiStatusEvent.num++;
    gizwitsProtocol.wifiStatusData.rssi = status->ststus.types.rssi;
    GIZWITS_LOG("RSSI is %d \n", gizwitsProtocol.wifiStatusData.rssi);

    gizwitsProtocol.issuedFlag = WIFI_STATUS_TYPE;

    return 0;
}


/**@name Gizwits User API interface
* @{
*/

/**
* @brief gizwits Protocol initialization interface

* Protocol-related timer, serial port initialization

* Datapoint initialization

* @param none
* @return none
*/
void gizwitsInit(void)
{    
    pRb.rbCapacity = RB_MAX_LEN;
    pRb.rbBuff = rbBuf;
    if(0 == rbCreate(&pRb))
	{
		GIZWITS_LOG("rbCreate Success \n");
	}
	else
	{
		GIZWITS_LOG("rbCreate Faild \n");
	}
    
    memset((uint8_t *)&gizwitsProtocol, 0, sizeof(gizwitsProtocol_t));
}

/**
* @brief WiFi configure interface

* Set the WiFi module into the corresponding configuration mode or reset the module

* @param[in] mode ：0x0， reset the module ;0x01， SoftAp mode ;0x02， AirLink mode ;0x03， Production test mode; 0x04:allow users to bind devices

* @return Error command code
*/
int32_t gizwitsSetMode(uint8_t mode)
{
    int32_t ret = 0;
    protocolCfgMode_t cfgMode;
    protocolCommon_t setDefault;

    switch(mode)
    {
        case WIFI_RESET_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_SET_DEFAULT;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t));   
            break;
        case WIFI_SOFTAP_MODE:
            gizProtocolHeadInit((protocolHead_t *)&cfgMode);
            cfgMode.head.cmd = CMD_WIFI_CONFIG;
            cfgMode.head.sn = gizwitsProtocol.sn++;
            cfgMode.cfgMode = mode;
            cfgMode.head.len = exchangeBytes(sizeof(protocolCfgMode_t)-4);
            cfgMode.sum = gizProtocolSum((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            ret = uartWrite((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }
            gizProtocolWaitAck((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t)); 
            break;
        case WIFI_AIRLINK_MODE:
            gizProtocolHeadInit((protocolHead_t *)&cfgMode);
            cfgMode.head.cmd = CMD_WIFI_CONFIG;
            cfgMode.head.sn = gizwitsProtocol.sn++;
            cfgMode.cfgMode = mode;
            cfgMode.head.len = exchangeBytes(sizeof(protocolCfgMode_t)-4);
            cfgMode.sum = gizProtocolSum((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            ret = uartWrite((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }
            gizProtocolWaitAck((uint8_t *)&cfgMode, sizeof(protocolCfgMode_t)); 
            break;
        case WIFI_PRODUCTION_TEST:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_PRODUCTION_TEST;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            break;
        case WIFI_NINABLE_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_NINABLE_MODE;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t)); 
            break;
        case WIFI_REBOOT_MODE:
            gizProtocolHeadInit((protocolHead_t *)&setDefault);
            setDefault.head.cmd = CMD_REBOOT_MODULE;
            setDefault.head.sn = gizwitsProtocol.sn++;
            setDefault.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
            setDefault.sum = gizProtocolSum((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            ret = uartWrite((uint8_t *)&setDefault, sizeof(protocolCommon_t));
            if(ret < 0)
            {
                GIZWITS_LOG("ERR: uart write error %d \n", ret);
            }

            gizProtocolWaitAck((uint8_t *)&setDefault, sizeof(protocolCommon_t)); 
            break;
        default:
            GIZWITS_LOG("ERR: CfgMode error!\n");
            break;
    }

    return ret;
}

/**
* @brief Get the the network time

* Protocol 4.13:"Device MCU send" of "the MCU requests access to the network time"

* @param[in] none
* @return none
*/
void gizwitsGetNTP(void)
{
    int32_t ret = 0;
    protocolCommon_t getNTP;

    gizProtocolHeadInit((protocolHead_t *)&getNTP);
    getNTP.head.cmd = CMD_GET_NTP;
    getNTP.head.sn = gizwitsProtocol.sn++;
    getNTP.head.len = exchangeBytes(sizeof(protocolCommon_t)-4);
    getNTP.sum = gizProtocolSum((uint8_t *)&getNTP, sizeof(protocolCommon_t));
    ret = uartWrite((uint8_t *)&getNTP, sizeof(protocolCommon_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR[NTP]: uart write error %d \n", ret);
    }

    gizProtocolWaitAck((uint8_t *)&getNTP, sizeof(protocolCommon_t));
}


/**
* @brief Get Module Info

* 

* @param[in] none
* @return none
*/
void gizwitsGetModuleInfo(void)
{
    int32_t ret = 0;
    protocolGetModuleInfo_t getModuleInfo;

    gizProtocolHeadInit((protocolHead_t *)&getModuleInfo);
    getModuleInfo.head.cmd = CMD_ASK_MODULE_INFO;
    getModuleInfo.head.sn = gizwitsProtocol.sn++;
    getModuleInfo.type = 0x0;
    getModuleInfo.head.len = exchangeBytes(sizeof(protocolGetModuleInfo_t)-4);
    getModuleInfo.sum = gizProtocolSum((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
    ret = uartWrite((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
    if(ret < 0)
    {
        GIZWITS_LOG("ERR[NTP]: uart write error %d \n", ret);
    }

    gizProtocolWaitAck((uint8_t *)&getModuleInfo, sizeof(protocolGetModuleInfo_t));
}


/**
* @brief Module Info Analyse
*
* @param [in] head : 
*
* @return 0, Success， , other,Faild
*/
static int8_t gizProtocolModuleInfoHandle(protocolHead_t *head)
{
    protocolModuleInfo_t *moduleInfo = (protocolModuleInfo_t *)head;

    if(NULL == head)
    {
        GIZWITS_LOG("NTP is empty \n");
        return -1;
    }

    memcpy((uint8_t *)&gizwitsProtocol.wifiModuleNews,(uint8_t *)&moduleInfo->wifiModuleInfo, sizeof(moduleInfo_t));

    gizwitsProtocol.moduleInfoEvent.event[gizwitsProtocol.moduleInfoEvent.num] = MODULE_INFO;
    gizwitsProtocol.moduleInfoEvent.num++;

    gizwitsProtocol.issuedFlag = GET_MODULEINFO_TYPE;


    return 0;
}

/**
* @brief Protocol handling function

* 

* @param [in] currentData :The protocol data pointer
* @return none
*/
int32_t gizwitsHandle(dataPoint_t *currentData)
{
    int8_t ret = 0;
#ifdef PROTOCOL_DEBUG
    uint16_t i = 0;
#endif
    uint8_t ackData[RB_MAX_LEN];
    uint16_t protocolLen = 0;
    uint32_t ackLen = 0;
    protocolHead_t *recvHead = NULL;
    char *didPtr = NULL;
    uint16_t offset = 0;


    if(NULL == currentData)
    {
        GIZWITS_LOG("GizwitsHandle Error , Illegal Param\n");
        return -1;
    }

    /*resend strategy*/
    gizProtocolAckHandle();
    ret = gizProtocolGetOnePacket(&pRb, gizwitsProtocol.protocolBuf, &protocolLen);

    if(0 == ret)
    {
        GIZWITS_LOG("Get One Packet!\n");
        
#ifdef PROTOCOL_DEBUG
        GIZWITS_LOG("WiFi2MCU[%4d:%4d]: ", gizGetTimerCount(), protocolLen);
        for(i=0; i<protocolLen;i++)
        {
            GIZWITS_LOG("%02x ", gizwitsProtocol.protocolBuf[i]);
        }
        GIZWITS_LOG("\n");
#endif

        recvHead = (protocolHead_t *)gizwitsProtocol.protocolBuf;
        switch (recvHead->cmd)
        {
            case CMD_GET_DEVICE_INTO:
                gizProtocolGetDeviceInfo(recvHead);
                break;
            case CMD_ISSUED_P0:
                GIZWITS_LOG("flag %x %x \n", recvHead->flags[0], recvHead->flags[1]);
                //offset = 1;
               
                if(0 == gizProtocolIssuedProcess(didPtr, gizwitsProtocol.protocolBuf+sizeof(protocolHead_t)+offset, protocolLen-(sizeof(protocolHead_t)+offset+1), ackData, &ackLen))
                {
                    gizProtocolIssuedDataAck(recvHead, ackData, ackLen,recvHead->flags[1]);
                    GIZWITS_LOG("AckData : \n");
                }
                break;
            case CMD_HEARTBEAT:
                gizProtocolCommonAck(recvHead);
                break;
            case CMD_WIFISTATUS:
                gizProtocolCommonAck(recvHead);
                gizProtocolModuleStatus((protocolWifiStatus_t *)recvHead);
                break;
            case ACK_REPORT_P0:
            case ACK_WIFI_CONFIG:
            case ACK_SET_DEFAULT:
            case ACK_NINABLE_MODE:
            case ACK_REBOOT_MODULE:
                gizProtocolWaitAckCheck(recvHead);
                break;
            case CMD_MCU_REBOOT:
                gizProtocolCommonAck(recvHead);
                GIZWITS_LOG("report:MCU reboot!\n");
                
                gizProtocolReboot();
                break;
            case CMD_ERROR_PACKAGE:
                break;
            case ACK_PRODUCTION_TEST:
                gizProtocolWaitAckCheck(recvHead);
                GIZWITS_LOG("Ack PRODUCTION_MODE success \n");
                break;           
            case ACK_GET_NTP:
                gizProtocolWaitAckCheck(recvHead);
                gizProtocolNTP(recvHead);
                GIZWITS_LOG("Ack GET_UTT success \n");
                break; 
            case ACK_ASK_MODULE_INFO:
                gizProtocolWaitAckCheck(recvHead);
                gizProtocolModuleInfoHandle(recvHead);
                GIZWITS_LOG("Ack GET_Module success \n");
            break;
 
            default:
                gizProtocolErrorCmd(recvHead,ERROR_CMD);
                GIZWITS_LOG("ERR: cmd code error!\n");
                break;
        }
    }
    else if(-2 == ret)
    {
        //Check failed, report exception
        recvHead = (protocolHead_t *)gizwitsProtocol.protocolBuf;
        gizProtocolErrorCmd(recvHead,ERROR_ACK_SUM);
        GIZWITS_LOG("ERR: check sum error!\n");
        return -2;
    }
    
    switch(gizwitsProtocol.issuedFlag)
    {
        case ACTION_CONTROL_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.issuedProcessEvent, (uint8_t *)&gizwitsProtocol.gizCurrentDataPoint, sizeof(dataPoint_t));
            memset((uint8_t *)&gizwitsProtocol.issuedProcessEvent,0x0,sizeof(gizwitsProtocol.issuedProcessEvent));  
            break;
        case WIFI_STATUS_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.wifiStatusEvent, (uint8_t *)&gizwitsProtocol.wifiStatusData, sizeof(moduleStatusInfo_t));
            memset((uint8_t *)&gizwitsProtocol.wifiStatusEvent,0x0,sizeof(gizwitsProtocol.wifiStatusEvent));
            break;
        case ACTION_W2D_TRANSPARENT_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.issuedProcessEvent, (uint8_t *)gizwitsProtocol.transparentBuff, gizwitsProtocol.transparentLen);
            break;
        case GET_NTP_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.NTPEvent, (uint8_t *)&gizwitsProtocol.TimeNTP, sizeof(protocolTime_t));
            memset((uint8_t *)&gizwitsProtocol.NTPEvent,0x0,sizeof(gizwitsProtocol.NTPEvent));
            break;
        case GET_MODULEINFO_TYPE:
            gizwitsProtocol.issuedFlag = STATELESS_TYPE;
            gizwitsEventProcess(&gizwitsProtocol.moduleInfoEvent, (uint8_t *)&gizwitsProtocol.wifiModuleNews, sizeof(moduleInfo_t));
            memset((uint8_t *)&gizwitsProtocol.moduleInfoEvent,0x0,sizeof(moduleInfo_t));
            break;
        default:
            break;      
    }

    gizDevReportPolicy(currentData);

    return 0;
}

/**
* @brief gizwits report transparent data interface

* The user can call the interface to complete the reporting of private protocol data

* @param [in] data :Private protocol data
* @param [in] len  :Private protocol data length
* @return 0，success ;other，failure
*/
int32_t gizwitsPassthroughData(uint8_t * gizdata, uint32_t len)
{
	int32_t ret = 0;
	uint8_t tx_buf[MAX_PACKAGE_LEN];
	uint8_t *pTxBuf = tx_buf;
	uint16_t data_len = 6+len;
    if(NULL == gizdata)
    {
        GIZWITS_LOG("[ERR] gizwitsPassthroughData Error \n");
        return (-1);
    }

	*pTxBuf ++= 0xFF;
	*pTxBuf ++= 0xFF;
	*pTxBuf ++= (uint8_t)(data_len>>8);//len
	*pTxBuf ++= (uint8_t)(data_len);
	*pTxBuf ++= CMD_REPORT_P0;//0x1b cmd
	*pTxBuf ++= gizwitsProtocol.sn++;//sn
	*pTxBuf ++= 0x00;//flag
	*pTxBuf ++= 0x00;//flag
	*pTxBuf ++= ACTION_D2W_TRANSPARENT_DATA;//P0_Cmd

    memcpy(&tx_buf[9],gizdata,len);
    tx_buf[data_len + 4 - 1 ] = gizProtocolSum( tx_buf , (data_len+4));
    
	ret = uartWrite(tx_buf, data_len+4);
    if(ret < 0)
    {
        GIZWITS_LOG("ERR: uart write error %d \n", ret);
    }

    gizProtocolWaitAck(tx_buf, data_len+4);

    return 0;
}

/**@} */
