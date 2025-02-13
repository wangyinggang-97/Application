/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Memory_Clr(uint8_t*,uint16_t);   //�ڴ��������

/* Public variables-----------------------------------------------------------*/
Public_t  Public = 
{
  Memory_Clr
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   Memory_Set
	* @brief  �ڴ��������
	* @param  pucBuffer -> �ڴ��׵�ַ
						LEN       -> �ڴ泤��   
	* @retval None      
*/
static void Memory_Clr(uint8_t* pucBuffer,uint16_t LEN)
{
	uint16_t i;
	
	for(i=0;i<LEN;i++)
	{
		*(pucBuffer+i) = (uint8_t)0;
	}
}

/*
	* @name   fputc
	* @brief  fputcӳ��������
	* @param  ch -> �������ַ�
	* @retval ch -> �ѷ����ַ�      
*/
#ifdef __GNUC__									//?????????
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart_debug, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}


/*int fputc(int ch,FILE* f)
{
	//ͨ����ѯ�ķ�ʽѭ������
	HAL_UART_Transmit(&huart_debug, (uint8_t *)&ch, 1, 0x000A);

	return ch;
}*/
/********************************************************
  End Of File
********************************************************/
