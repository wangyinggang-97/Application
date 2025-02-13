#ifndef __Buzzer_H__
#define __Buzzer_H__

#include "MyApplication.h"

//定义枚举类型
typedef enum
{
	Buzzer_Status_ON  = (uint8_t)0x01,
	Buzzer_Status_OFF = (uint8_t)0x00,
}Buzzer_Status_t;

//定义结构体类型
typedef struct
{
	Buzzer_Status_t  Status;   //状态

	void (*ON)(void);     //打开
	void (*OFF)(void);    //关闭
} Buzzer_t;

/* extern variables-----------------------------------------------------------*/
extern Buzzer_t  Buzzer;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
