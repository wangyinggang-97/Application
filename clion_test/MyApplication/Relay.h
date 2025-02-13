#ifndef __Relay_H__
#define __Relay_H__

#include "MyApplication.h"

//定义枚举类型
typedef enum
{
	Relay_Status_ON  = (uint8_t)0x01,
	Relay_Status_OFF = (uint8_t)0x00,
}Relay_Status_t;


//定义结构体类型
typedef struct
{
	Relay_Status_t  Status;   //状态
	
	void (*Relay_ON)(void);     //打开
	void (*Relay_OFF)(void);    //关闭
	void (*Relay_Flip)(void);   //翻转
} Relay_t;

/* extern variables-----------------------------------------------------------*/
extern Relay_t  Relay;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
