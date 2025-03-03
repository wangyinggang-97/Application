#ifndef __Timer6_H__
#define __Timer6_H__

#include "MyApplication.h"

//定义结枚举类型
typedef enum{
	TIMER6_10mS  	= (uint16_t)2,
	TIMER6_50mS  	= (uint16_t)10,
	TIMER6_100mS	= (uint16_t)20,
	TIMER6_200mS	= (uint16_t)40,
	TIMER6_500mS	= (uint16_t)100,
	TIMER6_1S     = (uint16_t)200,
	TIMER6_2S     = (uint16_t)400,
	TIMER6_3S     = (uint16_t)600,
	TIMER6_5S     = (uint16_t)1000,
	TIMER6_10S    = (uint16_t)2000,
	TIMER6_3min   = (uint16_t)36000,
}TIMER6_Value_t;

//定义结构体类型
typedef struct
{
    uint16_t volatile usDelay_Timer;
	uint16_t volatile usMCU_Run_Timer;  //系统运行定时器
	
	void (*Timer6_Start_IT)(void);   //定时器6以中断模式启动
    void (*Delay_us)(uint16_t nus);   //定时器延时微妙
} Timer6_t;

/* extern variables-----------------------------------------------------------*/
extern Timer6_t  Timer6;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
