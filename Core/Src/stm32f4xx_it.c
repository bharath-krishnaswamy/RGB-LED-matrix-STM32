/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int address = 0;
int count = 0;
int clock = 0;
int increment = 0;

//initialise screen display text using a matrix:
int textmat[16][64] =
{
		{0,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,1},
		{1,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0},
		{1,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0},
		{0,0,0,1,0,1,0,0,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,1},
		{0,0,0,1,0,1,0,0,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1},
		{1,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		{0,3,3,3,0,3,3,3,0,0,0,3,3,0,0,3,0,0,3,0,3,0,0,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,3,0,3,3,0,3,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0},
		{3,0,3,3,0,3,3,3,0,0,3,0,0,3,0,3,0,0,3,0,3,0,3,3,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},
		{0,3,3,3,0,3,0,3,0,0,0,3,3,0,0,0,3,3,0,0,3,0,0,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},
		{3,3,3,3,0,3,0,0,0,0,0,3,3,0,0,0,3,3,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2},
		{3,0,0,0,0,3,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0},
		{3,3,3,0,0,3,0,0,0,0,3,0,0,3,0,3,0,0,3,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{3,0,0,0,0,3,3,3,3,0,0,3,3,0,0,0,3,3,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}


//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//
//		{1,0,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,2,2,0,0,2,2,2,0,0,2,2,2,0,0,2,0,0,0,2,2,2,2,0,0,2,2,0,2,2,2,2,0,0,2,2,0,0,0,2,2,0,0,0,2,2,0},
//		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,2,0,2,0,0,2,0,2,0,0,2,0,2,0,0,2},
//		{1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,0,0,1,0,2,0,0,2,2,2,2,0,0,2,2,0,0,2,0,0,0,2,2,2,0,0,2,0,0,0,0,0,2,0,0,0,2,2,0,0,2,0,0,2,0,2,0,0,2},
//		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,2,0,0,2,0,0,0,0,0,0,0,2,0,2,0,2,0,0,0,0,2,0,2,2,2,2,0,2,0,0,0,2,0,0,2,0,0,2,2,2,0,2,0,0,2},
//		{1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,2,0,2,2,2,2,0,0,0,2,0,2,0,0,2,0,2,0,0,0,2,0,0,2,0,0,0,0,2,0,2,0,0,2},
//		{1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,2,2,2,0,0,2,2,2,0,2,2,2,0,0,0,0,2,0,2,2,2,0,0,0,2,2,0,0,2,0,0,0,0,2,2,0,0,0,2,2,0,0,0,2,2,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void DisplayRed(void);
void DisplayViolet(void);
void SwitchAddress(void);
void DisplayData(int,int);
void DisplayNum(int,int,int);
void NumbertoMatrix(char*);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim10;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
//  if((count >= 0) && (count <= 31))
//  {
//	  HAL_GPIO_TogglePin(GPIOC, Clk_Pin);
//	  if(count % 2 == 1)
//		  DisplayRed();
//  }
//  count++;
//  if(count == 32)
//  {
////	  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(Lat_GPIO_Port, Lat_Pin, GPIO_PIN_SET);
//
//	  SwitchAddress();
//	  HAL_GPIO_WritePin(Lat_GPIO_Port, Lat_Pin, GPIO_PIN_RESET);
//	  count = 0;
//  }



  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim10);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  HAL_GPIO_TogglePin(Clk_GPIO_Port, Clk_Pin);

  if((HAL_GPIO_ReadPin(Clk_GPIO_Port, Clk_Pin) == GPIO_PIN_SET) && (count < 129))
  {
	  //code for testing

//	  if(count < 128)
//	  {
//		  if(count < 64)
//		  {
//			  if((address % 2 == 0))// && (count % 2 == 0))
//				  DisplayViolet1();
//			  else
//				  DisplayViolet2();
//		  }
//		  else if(address%2 == 0)
//			  DisplayRed();
//		  else
//			  DisplayWhite();
//
//		  count++;
//	  }


	  if((count/4)%2 == 0)
	  {
		  DisplayData(textmat[address + 4][count - ((count/4)*2)],textmat[address + 12][ count - ((count/4)*2)]);
	  }
	  else if((count/4)%2 == 1)
	  {
		  DisplayData(textmat[address][count - ((count/4)*2) - 2],textmat[address + 8][count - ((count/4)*2) - 2]);
	  }

	  count++;
  }

  if(count>128)
  {
	  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(Lat_GPIO_Port, Lat_Pin, GPIO_PIN_SET);
	  SwitchAddress();
	  HAL_GPIO_WritePin(Lat_GPIO_Port, Lat_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);
	  count = 0;
  }

  //halving brightness
  if(count%4 == 0)
  {
	  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);
  }
  else
	  HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void DisplayRed(void)
{
	HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
}

void DisplayViolet1(void)
{
	HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
}

void DisplayViolet2(void)
{
	HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_SET);
}
void DisplayWhite(void)
{
	HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
}

DisplayData(int a,int b)
{
	switch (a) {
		case 0:
			{
				HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_RESET);
			}
			break;
		case 1:
			{
				HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_SET);
			}
			break;
		case 2:
			{
				HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_RESET);
			}
			break;
		case 3:
			{
				HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_SET);
			}
			break;
		case 4:
			{
				HAL_GPIO_WritePin(GPIOC, R0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, B0_Pin, GPIO_PIN_RESET);
			}
			break;
		default:
			break;
	}
	switch (b) {
		case 0:
			{
				HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
			}
			break;
		case 1:
			{
				HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_SET);
			}
			break;
		case 2:
			{
				HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
			}
			break;
		case 3:
			{
				HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_SET);
			}
			break;
		case 4:
			{
				HAL_GPIO_WritePin(GPIOC, R1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, G1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, B1_Pin, GPIO_PIN_RESET);
			}
			break;
		default:
			break;
	}
}

void SwitchAddress(void)
{
	if(address == 0)//selects 4th,8th,12th,16th rows
	{
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
		address = 1;
	}
	else if(address == 1)//selects 3rd,7th,11th,15th rows
	{
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_RESET);
		address = 2;
	}
	else if(address == 2)//selects 2nd,6th,10th,14th rows
	{
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
		address = 3;
	}
	else if(address == 3)//selects 1st,5th,9th,13th rows
	{
		HAL_GPIO_WritePin(GPIOC, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, B_Pin, GPIO_PIN_SET);
		address = 0;
	}
}

//Function to display numerical data. Manipulates textmat matrix
void ChangeMatrix()
{
	int temp = slots_left;
	int i = 0;
	if(slots_left == 0)
		DisplayNum(1, i, slots_left);
	else if(slots_left != 0)
	{
		while(slots_left != 0)
		{
			temp = slots_left % 10;
			DisplayNum(1, i, temp);
			slots_left/=10;
			i++;
		}
	}

}

//Number to matrix conversion function
//Arguments: (free/occupied),(placeholder shift),(number value)
void DisplayNum(int forocc, int ph, int val)
{
	int index = (36 + 16(forocc - 1)) - (ph * 8);
	int m=0,n=0;
	switch (val) {
		case 0:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,4,4,4,4,0,0},
					{0,0,4,4,4,4,0,0},
					{0,4,4,0,0,4,4,0},
					{0,4,4,0,0,4,4,0},
					{0,4,4,0,0,4,4,0},
					{0,4,4,0,0,4,4,0},
					{0,0,4,4,4,4,0,0},
					{0,0,4,4,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 1:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,4,4,4,0,0,0},
					{0,4,4,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 2:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,4,4,4,4,0,0},
					{0,4,4,4,4,4,4,0},
					{0,0,0,0,0,4,4,0},
					{0,0,0,0,4,4,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,4,4,0,0,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 3:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,4,4,4,4,4,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,0,0,0,4,4,0},
					{0,0,4,4,4,4,0,0},
					{0,0,4,4,4,4,0,0},
					{0,0,0,0,0,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 4:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,0,4,4,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,0,0,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 5:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,4,4,4,0,0},
					{0,0,4,4,4,4,4,0},
					{0,0,0,0,0,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 6:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,4,4,0,0,0,0},
					{0,4,4,0,0,0,0,0},
					{0,4,4,4,4,0,0,0},
					{0,4,4,4,4,4,0,0},
					{0,4,4,0,0,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,4,4,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 7:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,0,0,4,4,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 8:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,4,4,4,4,0,0},
					{0,4,4,0,0,4,4,0},
					{0,0,4,4,4,4,0,0},
					{0,0,4,4,4,4,0,0},
					{0,0,4,0,0,4,4,0},
					{0,4,4,0,0,4,4,0},
					{0,4,4,4,4,4,4,0},
					{0,0,4,4,4,4,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		case 9:
		{
			int nummat[8][8] =
			{
					{0,0,0,0,0,0,0,0},
					{0,0,4,4,4,4,0,0},
					{0,4,4,4,4,4,4,0},
					{0,4,4,0,0,4,4,0},
					{0,0,4,4,4,4,4,0},
					{0,0,0,4,4,4,4,0},
					{0,0,0,0,4,4,0,0},
					{0,0,0,4,4,0,0,0},
					{0,0,4,4,0,0,0,0},
					{0,0,0,0,0,0,0,0}
			};
		}
		break;
		default:
			break;
	}
	//replace in matrix
		for(int x = 9; x <= 15; x++)
		{
			for(int y = index; y <= index+8; y++)
			{
				textmat[x][y] = nummat[m][n++];
			}
			m++;
			n=0;
		}
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
