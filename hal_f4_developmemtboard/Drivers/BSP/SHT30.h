#ifndef __SHT30__
#define __SHT30__

#include "MyApplication.h"

//�궨��
#define SHT30_ADDR  (uint8_t)(0x44 << 1) //��������ַ
//#define SHT30_ADDR  (unsigned char)(0x45 << 1) //��������ַ

#define	Write_CMD   0xFE
#define	Read_CMD    0x01

//#define    SHT30_ADDR_WRITE    0x44<<1         //10001000
//#define    SHT30_ADDR_READ     (0x44<<1)+1     //10001001

#define    SHT30_ADDR_WRITE    0x88         //10001000
#define    SHT30_ADDR_READ     0x89     //10001001


//����ö������
typedef enum
{
    /* �����λ���� */

    SOFT_RESET_CMD = 0x30A2,    
    /*
    ���β���ģʽ
    ������ʽ��Repeatability_CS_CMD
    CS��Clock stretching
    */
    HIGH_ENABLED_CMD    = 0x2C06,
    MEDIUM_ENABLED_CMD  = 0x2C0D,
    LOW_ENABLED_CMD     = 0x2C10,
    HIGH_DISABLED_CMD   = 0x2400,
    MEDIUM_DISABLED_CMD = 0x240B,
    LOW_DISABLED_CMD    = 0x2416,

    /*
    ���ڲ���ģʽ
    ������ʽ��Repeatability_MPS_CMD
    MPS��measurement per second
    */
    HIGH_0_5_CMD   = 0x2032,
    MEDIUM_0_5_CMD = 0x2024,
    LOW_0_5_CMD    = 0x202F,
    HIGH_1_CMD     = 0x2130,
    MEDIUM_1_CMD   = 0x2126,
    LOW_1_CMD      = 0x212D,
    HIGH_2_CMD     = 0x2236,
    MEDIUM_2_CMD   = 0x2220,
    LOW_2_CMD      = 0x222B,
    HIGH_4_CMD     = 0x2334,
    MEDIUM_4_CMD   = 0x2322,
    LOW_4_CMD      = 0x2329,
    HIGH_10_CMD    = 0x2737,
    MEDIUM_10_CMD  = 0x2721,
    LOW_10_CMD     = 0x272A,
    /* ���ڲ���ģʽ��ȡ�������� */
    READOUT_FOR_PERIODIC_MODE = 0xE000,
} SHT30_CMD;

//����ö������

//����ṹ������

typedef struct
{
	uint8_t temp_array[6];
	float   fTemperature;  //�¶� -40��125��    ����0.1�� 
	uint8_t ucHumidity;    //ʪ�� 0%RH��100%RH  ����1%RH           
	
	void (*Measure_Period_Mode)(void);  //���ڲ���ģʽ
}SHT30_t;

/* extern variables-----------------------------------------------------------*/
extern SHT30_t  SHT30;

uint8_t SHT30_Init(void);
#endif
/********************************************************
  End Of File
********************************************************/
