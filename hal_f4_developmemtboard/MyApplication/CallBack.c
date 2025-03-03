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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{


}
/*
	* @name   HAL_TIM_PeriodElapsedCallback
	* @brief  ??????ж???????
	* @param  *htim -> ???????????????
	* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == htim6.Instance)
    {
        if(++Timer6.usMCU_Run_Timer >= TIMER6_1S)
        {
            Timer6.usMCU_Run_Timer = 0;
            LED.LED_Flip(LED0);
        }
        lv_tick_inc(5);
    }
}

