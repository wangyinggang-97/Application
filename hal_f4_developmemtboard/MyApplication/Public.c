/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Public variables-----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/


/*
	* @name   fputc
	* @brief  fputcӳ��������
	* @param  ch -> �������ַ�
	* @retval ch -> �ѷ����ַ�      
*/
int fputc(int ch,FILE* f)
{
	//ͨ����ѯ�ķ�ʽѭ������
	HAL_UART_Transmit(&huart_debug, (uint8_t *)&ch, 1, 0x000A);

	return ch;
}
//�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{		
	int ch;
	HAL_UART_Receive(&huart_debug, (uint8_t *)&ch, 1,0xFFFF);	
	return (ch);
}

/********************************************************
  End Of File
********************************************************/
