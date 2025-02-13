/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Public variables-----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/      

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//KEY1
	if(GPIO_Pin == KEY1_Pin)
	{
		
	}
	//KEY2
	if(GPIO_Pin == KEY2_Pin)
	{
		
	}
  //KEY3
	if(GPIO_Pin == KEY3_Pin)
	{	
		
	}
	//KEY4
	if(GPIO_Pin == KEY4_Pin)
	{	

	}
}*/

/*
	* @name   HAL_TIM_PeriodElapsedCallback
	* @brief  ��ʱ���жϻص�����
	* @param  *htim -> ����ʱ���Ľṹ��ָ��
	* @retval None      
*/   
//���STM32cubeMX���˻ص�������ֲmain.c�ļ���
/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim6.Instance)
	{
		Timer6.usDelay_Timer++;
		Timer6.SHT30_Measure_Timeout++;
		ESP8266.TCP_Reconnect_Timer++;
	}
	
	//���Ʋ������
	if(htim->Instance == htim7.Instance)
	{
		//ûת��ָ����Ȧ��
		if(Unipolar_Step_Motor.Circle > 0)
		{
			//���ת��һ������
			Unipolar_Step_Motor.Step_One_Pulse();
			
			//������������ж��Ƿ�ת����һȦ
			if(++Unipolar_Step_Motor.Pulse_Cnt == Unipolar_Step_Motor.One_Circle_Pulse)
			{
				Unipolar_Step_Motor.Pulse_Cnt = 0;
				//ת��Ȧ����һ
				Unipolar_Step_Motor.Circle--;
			}
		}
		//��ת��ָ����Ȧ��
		else
		{
			Unipolar_Step_Motor.Status = Stop_State;
			CLR_Motor_A;
			CLR_Motor_B;
			CLR_Motor_C;
			CLR_Motor_D;
			LED.LED_OFF(LED2);
		}
	}
}*/

/*
	* @name   HAL_UART_IdleCallback
	* @brief  ���ڿ����жϻص�����
	* @param  *htim -> �����ڵĽṹ��ָ��
	* @retval None      
*/
void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart2.Instance)
	{
		ESP8266.Receive_Information();
	}
}
/********************************************************
  End Of File
********************************************************/
