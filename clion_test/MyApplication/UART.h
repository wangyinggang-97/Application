#ifndef __UART_H_
#define __UART_H_

#include "MyApplication.h"

//����ö������
typedef enum
{	
	TTL       = (uint8_t)0,
	RS_485	  = (uint8_t)1,
	RS_232	  = (uint8_t)2,
}Interface_Type_t;

//�����첽���ڽṹ������
typedef struct
{
	uint8_t* pucSend_Buffer;           //���ͻ���ָ�� 
	uint8_t* pucRec_Buffer;            //���ջ���ָ�� 
	
	void (*SendArray)(uint8_t*,uint16_t);  //���ڷ�������
	void (*SendString)(uint8_t*);          //���ڷ����ַ���

	uint8_t	Interface_Type;            //�ӿ�����
	void (*RS485_Set_SendMode)(void);  //RS-485�ӿ�����Ϊ����ģʽ
	void (*RS485_Set_RecMode)(void);   //RS-485�ӿ�����Ϊ����ģʽ
	
} UART_t;

/* extern variables-----------------------------------------------------------*/

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/

