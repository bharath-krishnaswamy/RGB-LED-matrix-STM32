/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
uint8_t data[2];
int slots_left;
int slots_occ;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void ChangeMatrix(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define R0_Pin GPIO_PIN_0
#define R0_GPIO_Port GPIOC
#define G0_Pin GPIO_PIN_1
#define G0_GPIO_Port GPIOC
#define B0_Pin GPIO_PIN_2
#define B0_GPIO_Port GPIOC
#define R1_Pin GPIO_PIN_3
#define R1_GPIO_Port GPIOC
#define G1_Pin GPIO_PIN_4
#define G1_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_5
#define B1_GPIO_Port GPIOC
#define A_Pin GPIO_PIN_6
#define A_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_7
#define B_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_8
#define C_GPIO_Port GPIOC
#define D_Pin GPIO_PIN_9
#define D_GPIO_Port GPIOC
#define clk2_Pin GPIO_PIN_15
#define clk2_GPIO_Port GPIOA
#define Clk_Pin GPIO_PIN_10
#define Clk_GPIO_Port GPIOC
#define Lat_Pin GPIO_PIN_11
#define Lat_GPIO_Port GPIOC
#define OE_Pin GPIO_PIN_12
#define OE_GPIO_Port GPIOC
#define clk3_Pin GPIO_PIN_0
#define clk3_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
