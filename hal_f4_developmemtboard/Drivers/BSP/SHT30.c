/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
void Measure_Period_Mode(void);  //���ڲ���ģʽ

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
 * @brief    ��SHT30����һ��ָ��(16bit)
 * @param    cmd ���� SHT30ָ���SHT30_MODE��ö�ٶ��壩
 * @retval    �ɹ�����HAL_OK
*/
static uint8_t  SHT30_Send_Cmd(SHT30_CMD cmd)
{
    uint8_t cmd_buffer[2];
    cmd_buffer[0] = cmd >> 8;
    cmd_buffer[1] = cmd;
    return HAL_I2C_Master_Transmit(&hi2c1, SHT30_ADDR_WRITE, (uint8_t*) cmd_buffer, 2, 0xFFFF);
} 
/**
 * @brief    ��λSHT30
 * @param    none
 * @retval    none
*/
void SHT30_reset(void)
{
    SHT30_Send_Cmd(SOFT_RESET_CMD);
    HAL_Delay(20);
}

/**
 * @brief    ��ʼ��SHT30
 * @param    none
 * @retval    �ɹ�����HAL_OK
 * @note    ���ڲ���ģʽ
*/
uint8_t SHT30_Init(void)
{
    return SHT30_Send_Cmd(MEDIUM_2_CMD);
}
/**
 * @brief    ��SHT30��ȡһ������
 * @param    dat ���� �洢��ȡ���ݵĵ�ַ��6���ֽ����飩
 * @retval    �ɹ� ���� ����HAL_OK
*/
uint8_t SHT30_Read_Dat(uint8_t* dat)
{
    SHT30_Send_Cmd(READOUT_FOR_PERIODIC_MODE);
    return HAL_I2C_Master_Receive(&hi2c1, SHT30_ADDR_READ, dat, 6, 0xFFFF);
}

/*
	* @name   Measure_Period_Mode
	* @brief  ���ڲ���ģʽ
	* @param  None
	* @retval None
*/
static void Measure_Period_Mode(void)
{
    uint16_t  temp_uint     = 0;
    double    temp_float    = 0;

    //���������Բ���
    if(SHT30_Read_Dat(SHT30.temp_array) == HAL_OK)
		{
			/* У���¶����ݺ�ʪ�������Ƿ������ȷ */
			//////�����¶�,����0.1
			if(CRC_8(SHT30.temp_array,2) == SHT30.temp_array[2]) //CRC-8 У��
			{
				temp_uint         = SHT30.temp_array[0]*256+SHT30.temp_array[1];
				temp_float        = ((double)temp_uint)*0.267032-4500;
				SHT30.fTemperature = temp_float*0.01;
			}
			
			//////����ʪ�ȣ�����1%RH
			if(CRC_8(&SHT30.temp_array[3],2) == SHT30.temp_array[5]) //CRC-8 У��
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
	* @brief  CRC-8У��
	* @param  Crc_ptr -> У�������׵�ַ
						LEN     -> У�����ݳ���
	* @retval CRC_Value -> У��ֵ
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
