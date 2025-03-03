/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Public variables-----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/


/*
	* @name   fputc
	* @brief  fputc映射物理串口
	* @param  ch -> 待发送字符
	* @retval ch -> 已发送字符      
*/
int fputc(int ch,FILE* f)
{
	//通过查询的方式循环发送
	HAL_UART_Transmit(&huart_debug, (uint8_t *)&ch, 1, 0x000A);

	return ch;
}
//重定向c库函数scanf到串口DEBUG_USART，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{		
	int ch;
	HAL_UART_Receive(&huart_debug, (uint8_t *)&ch, 1,0xFFFF);	
	return (ch);
}

/********************************************************
  End Of File
********************************************************/
