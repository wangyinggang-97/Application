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

//������б���
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
        printf("������Ϣ����1ʧ��\r\n");
    else
        printf("������Ϣ����1�ɹ�\r\n");

    xQueue2 = xQueueCreate(2, 16);
    if(xQueue2 == NULL)
        printf("������Ϣ����2ʧ��\r\n");
    else
        printf("������Ϣ����2�ɹ�\r\n");
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
    uint8_t CPU_RunInfo[500];  //������������ʱ����Ϣ
    uint32_t ucSend_Data = 0;  //����Ϣ����1���͵�����
    const TickType_t ulSendBlockTime = pdMS_TO_TICKS(10);
    /* Infinite loop */
    for(;;)
    {
        //�������
        KEY.GetKeyCode();

        //KEY1����
        if(KEY.KeyCode == KEY1)
        {
            vTaskList((char*)&CPU_RunInfo);
            printf("---------------------------------\r\n");
            printf("������               ����״̬  ���ȼ�   ʣ��ջ �������\r\n");
            printf("%s",CPU_RunInfo);
            printf("---------------------------------\r\n");

            vTaskGetRunTimeStats((char*)&CPU_RunInfo);
            printf("---------------------------------\r\n");
            printf("������                 ���м���        ������\r\n");
            printf("%s",CPU_RunInfo);
            printf("---------------------------------\r\n");
        }

        //KEY2����
        if(KEY.KeyCode == KEY2)
        {
            if(xQueueSend(xQueue1, &ucSend_Data, ulSendBlockTime) == pdTRUE)
                printf("�ɹ�����Ϣ����1�������ݣ�%u\r\n", ucSend_Data);
            else
                printf("����Ϣ����1�������ݳ��ֳ�ʱ!!!\r\n");

            //���·��͵�����
            ucSend_Data += 1000;
        }

        //KEY3����
        if(KEY.KeyCode == KEY3)
        {
            if(xQueueSend(xQueue2, "MCU168168168\r\n", 0) == pdTRUE)
                printf("�ɹ�����Ϣ����2�����ַ�����%s\r\n", "MCU168168168");
            else
                printf("����Ϣ����2�����ַ������ֳ�ʱ!!!\r\n");
        }

        //KEY4����
        if(KEY.KeyCode == KEY4)
        {
            if(xQueueSend(xQueue2, "YJJY168168168", 0) == pdTRUE)
                printf("�ɹ�����Ϣ����2�����ַ�����%s\r\n", "YJJY168168168\r\n");
            else
                printf("����Ϣ����2�����ַ������ֳ�ʱ!!!\r\n");
        }

        //������ʱ20ms
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
            printf("�ɹ�������Ϣ����1�����ݣ�%u\r\n", ucRec_Data);
        }
        else
        {
            printf("������Ϣ����1�����ݳ��ֳ�ʱ!!!\r\n");
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
            printf("�ɹ�������Ϣ����2���ַ�����%s\r\n", ucRec_Data);
        }
    }
    /* USER CODE END Queue2_Receive_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
