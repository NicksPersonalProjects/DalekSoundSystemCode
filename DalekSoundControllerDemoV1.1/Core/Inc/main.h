/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWMInput4_Blaster_Pin GPIO_PIN_0
#define PWMInput4_Blaster_GPIO_Port GPIOA
#define ADCVolume_Pin GPIO_PIN_1
#define ADCVolume_GPIO_Port GPIOA
#define PWMInput5_Pin GPIO_PIN_2
#define PWMInput5_GPIO_Port GPIOA
#define RedCtrl_Pin GPIO_PIN_3
#define RedCtrl_GPIO_Port GPIOA
#define TestButton_Pin GPIO_PIN_6
#define TestButton_GPIO_Port GPIOA
#define PWMInput6_Pin GPIO_PIN_4
#define PWMInput6_GPIO_Port GPIOC
#define PWMInput2_MainLights_Pin GPIO_PIN_6
#define PWMInput2_MainLights_GPIO_Port GPIOC
#define MainLightControl_Pin GPIO_PIN_8
#define MainLightControl_GPIO_Port GPIOC
#define BlueCtrl_Pin GPIO_PIN_9
#define BlueCtrl_GPIO_Port GPIOC
#define PWMInput1_DWTheme_Pin GPIO_PIN_8
#define PWMInput1_DWTheme_GPIO_Port GPIOA
#define PWMInput3_Exterminate_Pin GPIO_PIN_6
#define PWMInput3_Exterminate_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
