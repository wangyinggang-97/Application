#ifndef __KEY_H__
#define __KEY_H__

#include "MyApplication.h"

//定义枚举类型
typedef enum
{
	KEYNULL = 0,
	KEY1    = 1,
	KEY2    = 2,
	KEY3    = 3,
	KEY4    = 4
}KeyCode_t;


//定义结构体类型
typedef struct
{
	KeyCode_t  KeyCode;   //按键编码
	
	void (*GetKeyCode)(void);  //获取按键编码
} KEY_t;

/* extern variables-----------------------------------------------------------*/
extern KEY_t  KEY;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
