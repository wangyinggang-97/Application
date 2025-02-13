/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

static uint8_t  ucSend_Buffer[UART2_Send_LENGTH] = {0x00};
static uint8_t  ucRec_Buffer [UART2_Rec_LENGTH]  = {0x00};

/* Private function prototypes------------------------------------------------*/      
static void SendArray(uint8_t*,uint16_t);  //���ڷ�������
static void SendString(uint8_t*);          //���ڷ����ַ���

static void RS485_Set_SendMode(void); //RS-485�ӿ�����Ϊ����ģʽ
static void RS485_Set_RecMode(void);  //RS-485�ӿ�����Ϊ����ģʽ

/* Public variables-----------------------------------------------------------*/
UART_t  UART2 = 
{
	ucSend_Buffer,
	ucRec_Buffer,
	
	SendArray,
	SendString,
	
	TTL,
	RS485_Set_SendMode,
	RS485_Set_RecMode
};

/*
	* @name   SendArray
	* @brief  ���ڷ�������
	* @param  p_Arr:�����׵�ַ��LEN:���ͳ���
	* @retval None      
*/
static void SendArray(uint8_t* p_Arr,uint16_t LEN) 
{
	HAL_UART_Transmit_DMA(&huart2,p_Arr,LEN);
}


/*
	* @name   SendString
	* @brief  �����ַ���
	* @param  p_Str:�������ַ���
	* @retval None      
*/
static void SendString(uint8_t* p_Str) 
{	
	HAL_UART_Transmit_DMA(&huart2,p_Str,strlen((const char*)p_Str));
}

/*
	* @name   RS485_Set_SendMode
	* @brief  RS-485�ӿ�����Ϊ����ģʽ
	* @param  None
	* @retval None      
*/
static void RS485_Set_SendMode()
{

}

/*
	* @name   RS485_Set_RecMode
	* @brief  RS-485�ӿ�����Ϊ����ģʽ
	* @param  None
	* @retval None      
*/
static void RS485_Set_RecMode()
{
	
}
/********************************************************
  End Of File
********************************************************/
