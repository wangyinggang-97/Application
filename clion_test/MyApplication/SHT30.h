#ifndef __SHT30__
#define __SHT30__

#include "MyApplication.h"

//�궨��
#define SHT30_ADDR  (uint8_t)(0x44 << 1) //��������ַ
//#define SHT30_ADDR  (unsigned char)(0x45 << 1) //��������ַ

#define	Write_CMD   0xFE
#define	Read_CMD    0x01

//����ö������

//����ṹ������

typedef struct
{
	float   fTemperature;  //�¶� -40��125��    ����0.1�� 
	uint8_t ucHumidity;    //ʪ�� 0%RH��100%RH  ����1%RH           
	
	void (*Measure_Period_Mode)(void);  //���ڲ���ģʽ
}SHT30_t;

/* extern variables-----------------------------------------------------------*/
extern SHT30_t  SHT30;
#endif
/********************************************************
  End Of File
********************************************************/
