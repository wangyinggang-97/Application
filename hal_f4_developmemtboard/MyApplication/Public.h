#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include "MyApplication.h"
/* Public define-------------------------------------------------------------*/
#define SoftWare_Version 	(float)1.0
#define	huart_debug		huart1

static  uint32_t   fac_us=0;	
//����ö������ -> BITλ
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
//����ö������ -> TRUE/FALSEλ
typedef enum 
{
  FALSE = 0U, 
  TRUE = !FALSE
} FlagStatus_t;

//����ṹ������


/* extern variables-----------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart2_rx;

/*******Ԥ����궨��*******/

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
//#define Monitor_Run_Code   //�������м���� 
//#define Hardware_TEST      //Ӳ������

#endif
/********************************************************
  End Of File
********************************************************/
