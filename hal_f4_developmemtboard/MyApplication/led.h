#ifndef __led_H__
#define __led_H__


#include "MyApplication.h"

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
/********************************************************
  End Of File
********************************************************/

