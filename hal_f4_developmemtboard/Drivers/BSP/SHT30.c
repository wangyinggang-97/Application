/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
void Measure_Period_Mode(void);  //周期测量模式

/* Public variables-----------------------------------------------------------*/
SHT30_t SHT30 =
{
    {0, 0, 0, 0, 0, 0},
    0.0,
    0,
    Measure_Period_Mode
};

/* Private function prototypes------------------------------------------------*/
static uint8_t CRC_8(uint8_t *, uint8_t);

/**
 * @brief    向SHT30发送一条指令(16bit)
 * @param    cmd —— SHT30指令（在SHT30_MODE中枚举定义）
 * @retval    成功返回HAL_OK
*/
static uint8_t  SHT30_Send_Cmd(SHT30_CMD cmd)
{
    uint8_t cmd_buffer[2];
    cmd_buffer[0] = cmd >> 8;
    cmd_buffer[1] = cmd;
    return HAL_I2C_Master_Transmit(&hi2c1, SHT30_ADDR_WRITE, (uint8_t*) cmd_buffer, 2, 0xFFFF);
} 
/**
 * @brief    复位SHT30
 * @param    none
 * @retval    none
*/
void SHT30_reset(void)
{
    SHT30_Send_Cmd(SOFT_RESET_CMD);
    HAL_Delay(20);
}

/**
 * @brief    初始化SHT30
 * @param    none
 * @retval    成功返回HAL_OK
 * @note    周期测量模式
*/
uint8_t SHT30_Init(void)
{
    return SHT30_Send_Cmd(MEDIUM_2_CMD);
}
/**
 * @brief    从SHT30读取一次数据
 * @param    dat —— 存储读取数据的地址（6个字节数组）
 * @retval    成功 —— 返回HAL_OK
*/
uint8_t SHT30_Read_Dat(uint8_t* dat)
{
    SHT30_Send_Cmd(READOUT_FOR_PERIODIC_MODE);
    return HAL_I2C_Master_Receive(&hi2c1, SHT30_ADDR_READ, dat, 6, 0xFFFF);
}

/*
	* @name   Measure_Period_Mode
	* @brief  周期测量模式
	* @param  None
	* @retval None
*/
static void Measure_Period_Mode(void)
{
    uint16_t  temp_uint     = 0;
    double    temp_float    = 0;

    //启动周期性测量
    if(SHT30_Read_Dat(SHT30.temp_array) == HAL_OK)
		{
			/* 校验温度数据和湿度数据是否接收正确 */
			//////计算温度,精度0.1
			if(CRC_8(SHT30.temp_array,2) == SHT30.temp_array[2]) //CRC-8 校验
			{
				temp_uint         = SHT30.temp_array[0]*256+SHT30.temp_array[1];
				temp_float        = ((double)temp_uint)*0.267032-4500;
				SHT30.fTemperature = temp_float*0.01;
			}
			
			//////计算湿度，精度1%RH
			if(CRC_8(&SHT30.temp_array[3],2) == SHT30.temp_array[5]) //CRC-8 校验
			{
				temp_uint      = SHT30.temp_array[3]*256+SHT30.temp_array[4];
				temp_float     = ((double)temp_uint)*0.152590;
				temp_float     = temp_float*0.01;
				SHT30.ucHumidity = (unsigned char)temp_float;  
			}		
		}   
}

/*
	* @name   CRC_8
	* @brief  CRC-8校验
	* @param  Crc_ptr -> 校验数据首地址
						LEN     -> 校验数据长度
	* @retval CRC_Value -> 校验值
*/
#define CRC8_POLYNOMIAL 0x31
static uint8_t CRC_8(uint8_t *Crc_ptr,uint8_t LEN)
{
    uint8_t CRC_Value = 0xFF;
	uint8_t i = 0,j = 0;

	for(i=0;i<LEN;i++)
	{
		CRC_Value ^= *(Crc_ptr+i);
		for(j=0;j<8;j++)
		{
			if(CRC_Value & 0x80)
				CRC_Value = (CRC_Value << 1) ^ 0x31;
			else
				CRC_Value = (CRC_Value << 1);
		}
	}
	return CRC_Value;
}

/********************************************************
  End Of File
********************************************************/
