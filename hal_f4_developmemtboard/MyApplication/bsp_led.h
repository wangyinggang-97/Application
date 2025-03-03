/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "MyApplication.h"
#include "stdint.h"

//定义枚举类型
typedef enum {
	LED0=(uint8_t)0X01,
	LED1=(uint8_t)0X02,
}LED_Num_t;
//定义结构体类型
typedef struct{
 
	  void (*LED_ON)(uint8_t);   //打开
	  void (*LED_OFF)(uint8_t);   //关闭
	  void (*LED_Flip)(uint8_t);   //反转
}LED_t;

/* extern variables-----------------------------------------------------------*/
extern LED_t LED;
/* extern function prototypes-------------------------------------------------*/
#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
