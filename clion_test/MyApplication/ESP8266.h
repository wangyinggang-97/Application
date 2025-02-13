#ifndef __ESP8266__
#define __ESP8266__

#include "MyApplication.h"

//�궨��

//����ö������

//����ṹ������
typedef struct
{
	uint8_t TCP_Connect_Status;            //TCP����״̬
	uint16_t TCP_Reconnect_Timer;          //TCP������ʱ��
	uint8_t  SmartConifg_Flag;             //����������־λ

	void (*Init)(void);                    //ESP8266��ʼ��
  void (*SmartConifg)(void);             //WIFIģ������
	void (*TCP_Connect_Server)(void);      //ͨ��TCP���ӷ�����
	void (*Transfer_SHT30)(void);          //����SHT30����ʪ��
	void (*Receive_Information)(void);     //������Ϣ
	void (*DMA_Receive_Set)(void);         //DMA��������
	void (*Error)(void);                   //������
} ESP8266_t;

/* extern variables-----------------------------------------------------------*/

extern ESP8266_t ESP8266;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
