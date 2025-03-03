/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "MyApplication.h"
#include "stdint.h"

//����ö������
typedef enum {
	LED0=(uint8_t)0X01,
	LED1=(uint8_t)0X02,
}LED_Num_t;
//����ṹ������
typedef struct{
 
	  void (*LED_ON)(uint8_t);   //��
	  void (*LED_OFF)(uint8_t);   //�ر�
	  void (*LED_Flip)(uint8_t);   //��ת
}LED_t;

/* extern variables-----------------------------------------------------------*/
extern LED_t LED;
/* extern function prototypes-------------------------------------------------*/
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
