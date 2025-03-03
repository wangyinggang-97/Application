#ifndef __System_H__
#define __System_H__

#define PROJECT_NAME             "LVGL Project"     //手表名称
#define PROJECT_HARDWARE_VERSION  1.0      //硬件版本
#define PROJECT_SOFTWARE_VERSION  1.0       //软件版本


//定义结构体类型
typedef struct
{
	void (*Run)(void);
	void (*Error_Handler)(void);
	void (*Assert_Failed)(void);
} System_t;

/* extern variables-----------------------------------------------------------*/
extern System_t  System;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
