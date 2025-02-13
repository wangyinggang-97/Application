#ifndef __I2C__
#define __I2C__

#include "MyApplication.h"

//�궨��
//����ö������
typedef enum
{
	ACK	 = GPIO_PIN_RESET,
	NACK = GPIO_PIN_SET,
}ACK_Value_t;

//����ṹ������
typedef struct
{
	void (*Init)(void);  //I2C��ʼ��
	void (*Start)(void); //I2C��ʼ�ź�
	void (*Stop)(void);  //I2Cֹͣ�ź�
	ACK_Value_t (*Write_Byte)(uint8_t);      //I2Cд�ֽ�
	uint8_t     (*Read_Byte) (ACK_Value_t);  //I2C���ֽ�
}I2C_Soft_t;

/* extern variables-----------------------------------------------------------*/
extern I2C_Soft_t  I2C_Soft;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
