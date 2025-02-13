#ifndef __ESP8266__
#define __ESP8266__

#include "MyApplication.h"

//宏定义

//定义枚举类型

//定义结构体类型
typedef struct
{
	uint8_t TCP_Connect_Status;            //TCP连接状态
	uint16_t TCP_Reconnect_Timer;          //TCP重连定时器
	uint8_t  SmartConifg_Flag;             //智能配网标志位

	void (*Init)(void);                    //ESP8266初始化
  void (*SmartConifg)(void);             //WIFI模块配网
	void (*TCP_Connect_Server)(void);      //通过TCP连接服务器
	void (*Transfer_SHT30)(void);          //传送SHT30的温湿度
	void (*Receive_Information)(void);     //接收信息
	void (*DMA_Receive_Set)(void);         //DMA接收设置
	void (*Error)(void);                   //错误处理
} ESP8266_t;

/* extern variables-----------------------------------------------------------*/

extern ESP8266_t ESP8266;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
