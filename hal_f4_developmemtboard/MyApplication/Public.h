#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include "MyApplication.h"
/* Public define-------------------------------------------------------------*/
#define SoftWare_Version 	(float)1.0
#define	huart_debug		huart1

static  uint32_t   fac_us=0;	
//定义枚举类型 -> BIT位
typedef enum
{
	BIT0 = (uint8_t)(0x01 << 0),  
	BIT1 = (uint8_t)(0x01 << 1),  
	BIT2 = (uint8_t)(0x01 << 2),  
	BIT3 = (uint8_t)(0x01 << 3),  
	BIT4 = (uint8_t)(0x01 << 4),
	BIT5 = (uint8_t)(0x01 << 5),
	BIT6 = (uint8_t)(0x01 << 6),
	BIT7 = (uint8_t)(0x01 << 7),
}BIT_t;
//定义枚举类型 -> TRUE/FALSE位
typedef enum 
{
  FALSE = 0U, 
  TRUE = !FALSE
} FlagStatus_t;

//定义结构体类型


/* extern variables-----------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart2_rx;

/*******预编译宏定义*******/

#ifdef  huart_debug	
#define user_main_printf(format, ...) printf( format "\r\n", ##__VA_ARGS__)
#define user_main_info(format, ...)   printf("main info:" format "\r\n", ##__VA_ARGS__)
#define user_main_debug(format, ...)  printf("main debug:" format "\r\n", ##__VA_ARGS__)
#define user_main_error(format, ...)  printf("main error:" format "\r\n",##__VA_ARGS__)
#else
#define user_main_printf(format, ...)
#define user_main_info(format, ...)
#define user_main_debug(format, ...)
#define user_main_error(format, ...)
#endif
//#define Monitor_Run_Code   //代码运行监控器 
//#define Hardware_TEST      //硬件测试

#endif
/********************************************************
  End Of File
********************************************************/
