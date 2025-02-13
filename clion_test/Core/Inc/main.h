/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY3_Pin GPIO_PIN_2
#define KEY3_GPIO_Port GPIOE
#define KEY3_EXTI_IRQn EXTI2_IRQn
#define KEY4_Pin GPIO_PIN_3
#define KEY4_GPIO_Port GPIOE
#define KEY4_EXTI_IRQn EXTI3_IRQn
#define LED1_Pin GPIO_PIN_4
#define LED1_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOE
#define Step_Motor_A_Pin GPIO_PIN_1
#define Step_Motor_A_GPIO_Port GPIOF
#define Step_Motor_B_Pin GPIO_PIN_2
#define Step_Motor_B_GPIO_Port GPIOF
#define Step_Motor_C_Pin GPIO_PIN_3
#define Step_Motor_C_GPIO_Port GPIOF
#define Step_Motor_D_Pin GPIO_PIN_4
#define Step_Motor_D_GPIO_Port GPIOF
#define TM1620_STB_Pin GPIO_PIN_0
#define TM1620_STB_GPIO_Port GPIOC
#define TM1620_CLK_Pin GPIO_PIN_1
#define TM1620_CLK_GPIO_Port GPIOC
#define TM1620_DIN_Pin GPIO_PIN_2
#define TM1620_DIN_GPIO_Port GPIOC
#define WIFI_EN_Pin GPIO_PIN_11
#define WIFI_EN_GPIO_Port GPIOF
#define WIFI_RST_Pin GPIO_PIN_12
#define WIFI_RST_GPIO_Port GPIOF
#define TFT_LCD_BL_Pin GPIO_PIN_2
#define TFT_LCD_BL_GPIO_Port GPIOG
#define UART3_SP3485_DE_nRE_Pin GPIO_PIN_10
#define UART3_SP3485_DE_nRE_GPIO_Port GPIOG
#define SHT30_SCL_Pin GPIO_PIN_11
#define SHT30_SCL_GPIO_Port GPIOG
#define SHT30_SDA_Pin GPIO_PIN_12
#define SHT30_SDA_GPIO_Port GPIOG
#define Relay_Pin GPIO_PIN_13
#define Relay_GPIO_Port GPIOG
#define OUT_PNP_Pin GPIO_PIN_14
#define OUT_PNP_GPIO_Port GPIOG
#define OUT_NPN_Pin GPIO_PIN_15
#define OUT_NPN_GPIO_Port GPIOG
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOE
#define KEY1_EXTI_IRQn EXTI0_IRQn
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOE
#define KEY2_EXTI_IRQn EXTI1_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
