/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MyApplication.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern volatile uint32_t CPU_RunTime;

//定义队列变量
static QueueHandle_t xQueue1 = NULL;
static QueueHandle_t xQueue2 = NULL;

/* USER CODE END Variables */
osThreadId LED1Handle;
osThreadId KEYHandle;
osThreadId Queue1_ReceiveHandle;
osThreadId Queue2_ReceiveHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LED1_Task(void const * argument);
void KEY_Task(void const * argument);
void Queue1_Receive_Task(void const * argument);
void Queue2_Receive_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
    CPU_RunTime = 0;
}

__weak unsigned long getRunTimeCounterValue(void)
{
    return CPU_RunTime;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    xQueue1 = xQueueCreate(1, sizeof(uint32_t));
    if(xQueue1 == NULL)
        printf("创建消息队列1失败\r\n");
    else
        printf("创建消息队列1成功\r\n");

    xQueue2 = xQueueCreate(2, 16);
    if(xQueue2 == NULL)
        printf("创建消息队列2失败\r\n");
    else
        printf("创建消息队列2成功\r\n");
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of LED1 */
    osThreadDef(LED1, LED1_Task, osPriorityBelowNormal, 0, 128);
    LED1Handle = osThreadCreate(osThread(LED1), NULL);

    /* definition and creation of KEY */
    osThreadDef(KEY, KEY_Task, osPriorityAboveNormal, 0, 256);
    KEYHandle = osThreadCreate(osThread(KEY), NULL);

    /* definition and creation of Queue1_Receive */
    osThreadDef(Queue1_Receive, Queue1_Receive_Task, osPriorityNormal, 0, 128);
    Queue1_ReceiveHandle = osThreadCreate(osThread(Queue1_Receive), NULL);

    /* definition and creation of Queue2_Receive */
    osThreadDef(Queue2_Receive, Queue2_Receive_Task, osPriorityNormal, 0, 128);
    Queue2_ReceiveHandle = osThreadCreate(osThread(Queue2_Receive), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_LED1_Task */
/**
  * @brief  Function implementing the LED1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LED1_Task */
void LED1_Task(void const * argument)
{
    /* USER CODE BEGIN LED1_Task */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1000);
        LED.LED_Flip(LED1);
    }
    /* USER CODE END LED1_Task */
}

/* USER CODE BEGIN Header_KEY_Task */
/**
* @brief Function implementing the KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KEY_Task */
void KEY_Task(void const * argument)
{
    /* USER CODE BEGIN KEY_Task */
    uint8_t CPU_RunInfo[500];  //保存任务运行时间信息
    uint32_t ucSend_Data = 0;  //向消息队列1发送的数据
    const TickType_t ulSendBlockTime = pdMS_TO_TICKS(10);
    /* Infinite loop */
    for(;;)
    {
        //按键检测
        KEY.GetKeyCode();

        //KEY1处理
        if(KEY.KeyCode == KEY1)
        {
            vTaskList((char*)&CPU_RunInfo);
            printf("---------------------------------\r\n");
            printf("任务名               任务状态  优先级   剩余栈 任务序号\r\n");
            printf("%s",CPU_RunInfo);
            printf("---------------------------------\r\n");

            vTaskGetRunTimeStats((char*)&CPU_RunInfo);
            printf("---------------------------------\r\n");
            printf("任务名                 运行计数        利用率\r\n");
            printf("%s",CPU_RunInfo);
            printf("---------------------------------\r\n");
        }

        //KEY2处理
        if(KEY.KeyCode == KEY2)
        {
            if(xQueueSend(xQueue1, &ucSend_Data, ulSendBlockTime) == pdTRUE)
                printf("成功向消息队列1发送数据：%u\r\n", ucSend_Data);
            else
                printf("向消息队列1发送数据出现超时!!!\r\n");

            //更新发送的数据
            ucSend_Data += 1000;
        }

        //KEY3处理
        if(KEY.KeyCode == KEY3)
        {
            if(xQueueSend(xQueue2, "MCU168168168\r\n", 0) == pdTRUE)
                printf("成功向消息队列2发送字符串：%s\r\n", "MCU168168168");
            else
                printf("向消息队列2发送字符串出现超时!!!\r\n");
        }

        //KEY4处理
        if(KEY.KeyCode == KEY4)
        {
            if(xQueueSend(xQueue2, "YJJY168168168", 0) == pdTRUE)
                printf("成功向消息队列2发送字符串：%s\r\n", "YJJY168168168\r\n");
            else
                printf("向消息队列2发送字符串出现超时!!!\r\n");
        }

        //阻塞延时20ms
        osDelay(20);
    }
    /* USER CODE END KEY_Task */
}

/* USER CODE BEGIN Header_Queue1_Receive_Task */
/**
* @brief Function implementing the Queue1_Receive thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Queue1_Receive_Task */
void Queue1_Receive_Task(void const * argument)
{
    /* USER CODE BEGIN Queue1_Receive_Task */
    uint32_t ucRec_Data = 0;
    const TickType_t ulReceiveBlockTime = pdMS_TO_TICKS(1000);

    /* Infinite loop */
    for(;;)
    {
        if(xQueueReceive(xQueue1, &ucRec_Data, ulReceiveBlockTime) == pdTRUE)
        {
            printf("成功接收消息队列1的数据：%u\r\n", ucRec_Data);
        }
        else
        {
            printf("接收消息队列1的数据出现超时!!!\r\n");
        }
    }
    /* USER CODE END Queue1_Receive_Task */
}

/* USER CODE BEGIN Header_Queue2_Receive_Task */
/**
* @brief Function implementing the Queue2_Receive thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Queue2_Receive_Task */
void Queue2_Receive_Task(void const * argument)
{
    /* USER CODE BEGIN Queue2_Receive_Task */
    uint8_t ucRec_Data[16] = {0};
    /* Infinite loop */
    for(;;)
    {
        if(xQueueReceive(xQueue2, ucRec_Data, portMAX_DELAY) == pdTRUE)
        {
            printf("成功接收消息队列2的字符串：%s\r\n", ucRec_Data);
        }
    }
    /* USER CODE END Queue2_Receive_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
