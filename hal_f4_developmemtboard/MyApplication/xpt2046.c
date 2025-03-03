/**
  ************************************* Copyright ******************************
  *
  *                 (C) Copyright 2025,--,China, GCU.
  *                            All Rights Reserved
 */

/*include----------------------------------------------------------------------*/
#include "MyApplication.h"

/*define-----------------------------------------------------------------------*/

#define XPT2046_CS_LOW()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define XPT2046_CS_HIGH()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

#define CMD_X 0xD0  // 读取 X 坐标 (8-bit)
#define CMD_Y 0x90  // 读取 Y 坐标 (8-bit)
/*variate----------------------------------------------------------------------*/


/*statement--------------------------------------------------------------------*/


/*Function prototype Begin*****************************************************/

uint8_t XPT2046_Send(uint8_t data)
{
    uint8_t received_data;
    HAL_SPI_TransmitReceive(&hspi2, &data, &received_data, 1, 100);
    return received_data;
}


uint16_t XPT2046_Read(uint8_t cmd)
{
    XPT2046_CS_LOW();
    XPT2046_Send(cmd);  // 发送指令
    uint16_t high = XPT2046_Send(0x00);
    uint16_t low = XPT2046_Send(0x00);
    XPT2046_CS_HIGH();
    return ((high << 8) | low) >> 3;  // 12-bit 转换
}


void XPT2046_GetTouch(uint16_t *x, uint16_t *y)
{
    *x = XPT2046_Read(CMD_X);
    *y = XPT2046_Read(CMD_Y);
}

/*Function prototype End*******************************************************/





