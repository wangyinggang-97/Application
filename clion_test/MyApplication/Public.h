#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include "MyApplication.h"

/* Public define-------------------------------------------------------------*/
#define SoftWare_Version 	(float)1.1
#define	huart_debug		huart1

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

typedef enum
{
    FAILED = 0U,
    PASSED = !FAILED
} TestStatus_t;

//����ṹ������
typedef struct
{
    void (*Memory_Clr)(uint8_t*,uint16_t); //�ڴ������

} Public_t;

/* extern variables-----------------------------------------------------------*/
extern Public_t Public;

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

/*******Ԥ����궨��*******/
//#define Monitor_Run_Code   //�������м���� 
//#define Hardware_TEST      //Ӳ������

#endif
/********************************************************
  End Of File
********************************************************/
