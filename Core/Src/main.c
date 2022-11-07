/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void display7Seg(int , _Bool );
void display7Seg_2(int , _Bool );
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, RESET);
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);
  HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
  HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
  HAL_GPIO_WritePin(LED_2_3_GPIO_Port, LED_2_3_Pin, RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int counter = 0;
  int counter_2 = 0;
  int counter_3 = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  	  switch (counter) {
  		case 0:
  			counter_2= 5;
  			counter_3=3;
  			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
  			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
  			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);

  			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
  			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
  			HAL_GPIO_WritePin(LED_2_3_GPIO_Port, LED_2_3_Pin, RESET);
  			break;
  		case 3:
  			counter_3=2;
  			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, SET);
  			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, RESET);
  			HAL_GPIO_WritePin(LED_2_3_GPIO_Port, LED_2_3_Pin, SET);
  			break;
  		case 5:
  			counter_3=5;
  			counter_2= 3;
  			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
  			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
  			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);

  			HAL_GPIO_WritePin(LED_2_1_GPIO_Port, LED_2_1_Pin, RESET);
  			HAL_GPIO_WritePin(LED_2_2_GPIO_Port, LED_2_2_Pin, SET);
  			HAL_GPIO_WritePin(LED_2_3_GPIO_Port, LED_2_3_Pin, SET);
  			break;
  		case 8:
  			counter_2= 2;
  			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
  			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, RESET);
  			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
  			break;
  		default:
  			break;
  	}
    	display7Seg(counter_2, 1);
    	display7Seg_2(counter_3, 1);
  	  counter++;
  	  if(counter == 10){counter = 0;}
  	counter_2--;
  	counter_3--;

  	HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_2_1_Pin|LED_2_2_Pin|LED_2_3_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin|LED7_1_Pin|LED7_2_Pin
                          |LED7_3_Pin|LED7_4_Pin|LED7_5_Pin|LED7_6_Pin
                          |LED7_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED7_a_Pin|LED7_b_Pin|LED7_c_Pin|LED7_d_Pin
                          |LED7_e_Pin|LED7_f_Pin|LED7_g_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_2_1_Pin LED_2_2_Pin LED_2_3_Pin LED_RED_Pin
                           LED_YELLOW_Pin LED_GREEN_Pin LED7_1_Pin LED7_2_Pin
                           LED7_3_Pin LED7_4_Pin LED7_5_Pin LED7_6_Pin
                           LED7_7_Pin */
  GPIO_InitStruct.Pin = LED_2_1_Pin|LED_2_2_Pin|LED_2_3_Pin|LED_RED_Pin
                          |LED_YELLOW_Pin|LED_GREEN_Pin|LED7_1_Pin|LED7_2_Pin
                          |LED7_3_Pin|LED7_4_Pin|LED7_5_Pin|LED7_6_Pin
                          |LED7_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED7_a_Pin LED7_b_Pin LED7_c_Pin LED7_d_Pin
                           LED7_e_Pin LED7_f_Pin LED7_g_Pin */
  GPIO_InitStruct.Pin = LED7_a_Pin|LED7_b_Pin|LED7_c_Pin|LED7_d_Pin
                          |LED7_e_Pin|LED7_f_Pin|LED7_g_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7Seg(int decimalVal, _Bool LEDstatus)
{
	if(decimalVal > 9)
	{
		decimalVal = 0;
	}
	if(LEDstatus)
	{
		HAL_GPIO_WritePin(LED7_a_GPIO_Port, LED7_a_Pin, (decimalVal==1||decimalVal==4) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_b_GPIO_Port, LED7_b_Pin, (decimalVal==5||decimalVal==6) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_c_GPIO_Port, LED7_c_Pin, (decimalVal==2) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_d_GPIO_Port, LED7_d_Pin, (decimalVal==1||decimalVal==4 || decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_e_GPIO_Port, LED7_e_Pin, (decimalVal==1||decimalVal==4 || decimalVal==3 || decimalVal==5 || decimalVal==7 || decimalVal==9) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_f_GPIO_Port, LED7_f_Pin, (decimalVal==1||decimalVal==2||decimalVal==3||decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_g_GPIO_Port, LED7_g_Pin, (decimalVal==0||decimalVal==1||decimalVal==7) ? SET:RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED7_a_GPIO_Port, LED7_a_Pin, SET);
		HAL_GPIO_WritePin(LED7_b_GPIO_Port, LED7_b_Pin, SET);
		HAL_GPIO_WritePin(LED7_c_GPIO_Port, LED7_c_Pin, SET);
		HAL_GPIO_WritePin(LED7_d_GPIO_Port, LED7_d_Pin, SET);
		HAL_GPIO_WritePin(LED7_e_GPIO_Port, LED7_e_Pin, SET);
		HAL_GPIO_WritePin(LED7_f_GPIO_Port, LED7_f_Pin, SET);
		HAL_GPIO_WritePin(LED7_g_GPIO_Port, LED7_g_Pin, SET);
	}
}
void display7Seg_2(int decimalVal, _Bool LEDstatus)
{
	if(decimalVal > 9)
	{
		decimalVal = 0;
	}
	if(LEDstatus)
	{
		HAL_GPIO_WritePin(LED7_1_GPIO_Port, LED7_1_Pin, (decimalVal==1||decimalVal==4) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_2_GPIO_Port, LED7_2_Pin, (decimalVal==5||decimalVal==6) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_3_GPIO_Port, LED7_3_Pin, (decimalVal==2) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_4_GPIO_Port, LED7_4_Pin, (decimalVal==1||decimalVal==4 || decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_5_GPIO_Port, LED7_5_Pin, (decimalVal==1||decimalVal==4 || decimalVal==3 || decimalVal==5 || decimalVal==7 || decimalVal==9) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_6_GPIO_Port, LED7_6_Pin, (decimalVal==1||decimalVal==2||decimalVal==3||decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(LED7_7_GPIO_Port, LED7_7_Pin, (decimalVal==0||decimalVal==1||decimalVal==7) ? SET:RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED7_1_GPIO_Port, LED7_1_Pin, SET);
		HAL_GPIO_WritePin(LED7_2_GPIO_Port, LED7_2_Pin, SET);
		HAL_GPIO_WritePin(LED7_3_GPIO_Port, LED7_3_Pin, SET);
		HAL_GPIO_WritePin(LED7_4_GPIO_Port, LED7_4_Pin, SET);
		HAL_GPIO_WritePin(LED7_5_GPIO_Port, LED7_5_Pin, SET);
		HAL_GPIO_WritePin(LED7_6_GPIO_Port, LED7_6_Pin, SET);
		HAL_GPIO_WritePin(LED7_7_GPIO_Port, LED7_7_Pin, SET);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
