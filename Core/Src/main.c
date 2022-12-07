/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"button.h"
#include"software_timer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int current_fsm_state = 0;
#define NORMAL_MODE 0
#define MODE_2 	1
#define MODE_3 	2
#define MODE_4 	3
int led_scan_counter = 0;

int traffic_state = 0;

int time_red = 1000;
int time_yellow = 300;
int time_green = 700;
void display7Seg(int );
void custom_system_init();
void fsm_traffic_master();
void clear_led();
void setting_led_controller(int);
void timer_2_logic();
void traffic_state_controller();
extern int current_fsm_state;
void led_controller();
int display_val1;
int display_val2;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  custom_system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		fsm_traffic_master();
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, red1_Pin|green1_Pin|yellow1_Pin|red2_Pin
                          |e_Pin|d_Pin|c_Pin|b_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, green2_Pin|yellow2_Pin|en1_Pin|f_Pin
                          |a_Pin|g_Pin|en4_Pin|en3_Pin
                          |en2_Pin|status_led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : btn1_Pin btn2_Pin btn3_Pin */
  GPIO_InitStruct.Pin = btn1_Pin|btn2_Pin|btn3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : red1_Pin green1_Pin yellow1_Pin red2_Pin
                           e_Pin d_Pin c_Pin b_Pin */
  GPIO_InitStruct.Pin = red1_Pin|green1_Pin|yellow1_Pin|red2_Pin
                          |e_Pin|d_Pin|c_Pin|b_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : green2_Pin yellow2_Pin en1_Pin f_Pin
                           a_Pin g_Pin en4_Pin en3_Pin
                           en2_Pin status_led_Pin */
  GPIO_InitStruct.Pin = green2_Pin|yellow2_Pin|en1_Pin|f_Pin
                          |a_Pin|g_Pin|en4_Pin|en3_Pin
                          |en2_Pin|status_led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void custom_system_init()
{
	  traffic_state = 0;
	  display_val1 = time_green/100;
	  display_val2 = time_red/100;
	  timer_flag[0] = 1; // LED SCAN
	  timer_flag[1] = 1; //TRAFFIC TIME
	  timer_flag[2] = 0;
	  timer_flag[3] = 1;
	  setTimer(100,2); // 1 Second General
	  setTimer(25,3);
	  led_scan_counter = 0;
	  HAL_TIM_Base_Start_IT (& htim2 );
	  current_fsm_state = 0;
	  init_button(0);
	  init_button(1);
	  init_button(2);

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	timerRun(0); //LED SCAN
	timerRun(1); //Traffic Time
	timerRun(2);  // 1 second general
	timerRun(3); //2HZ Blinky
	getKeyInput(0);
	getKeyInput(1);
	getKeyInput(2);

}


void fsm_traffic_master()
{
	  if(keyPressFlag[0])
	  {
		  clear_led();
		  current_fsm_state +=1;
		  if(current_fsm_state > 3)current_fsm_state=0;
		  keyPressFlag[0] = 0;
	  }
	switch (current_fsm_state) {
		case NORMAL_MODE: // SCAN 7SEG, CONTROLL Traffic Status, Chech for Input Key
		  led_controller();
		  traffic_state_controller();
		  timer_2_logic();
			break;
		case MODE_2:
			if(keyPressFlag[2])
				  {
					  current_fsm_state = NORMAL_MODE;
					  keyPressFlag[2] = 0;
					  custom_system_init();
				  }
			setting_led_controller(current_fsm_state);
			if(keyPressFlag[1])
			{
				time_red = time_red + 100;
				keyPressFlag[1] = 0;
			}
			if(timer_flag[3])//Blinky led
			{
				HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
				HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
				HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin|yellow1_Pin, SET);
				HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin|yellow2_Pin, SET);
				setTimer(25,3);
			}
			break;
		case MODE_3:
			if(keyPressFlag[2])
				  {
					  current_fsm_state = NORMAL_MODE;
					  keyPressFlag[2] = 0;
					  custom_system_init();
				  }
			setting_led_controller(current_fsm_state);
			if(keyPressFlag[1])
			{
				time_yellow = time_yellow + 100;
				keyPressFlag[1] = 0;
			}
			if(timer_flag[3])
			{
				HAL_GPIO_TogglePin(yellow1_GPIO_Port, yellow1_Pin);
				HAL_GPIO_TogglePin(yellow2_GPIO_Port, yellow2_Pin);
				HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin|red1_Pin|red2_Pin, SET);
				HAL_GPIO_WritePin(green2_GPIO_Port,green2_Pin, SET);
				setTimer(25,3);
			}
			break;
		case MODE_4:
			if(keyPressFlag[2])
				  {
					  current_fsm_state = NORMAL_MODE;
					  keyPressFlag[2] = 0;
					  custom_system_init();
				  }
			setting_led_controller(current_fsm_state);
			if(keyPressFlag[1])
			{
				time_green = time_green + 100;
				keyPressFlag[1] = 0;
			}
			if(timer_flag[3])
			{
				HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
				HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
				HAL_GPIO_WritePin(red1_GPIO_Port, red2_Pin|red1_Pin|yellow1_Pin, SET);
				HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, SET);
				setTimer(25,3);
			}
			break;
		default:
			break;
	}
}
void timer_2_logic() // 1 second general timer
{
	if(timer_flag[2])
	{
		display_val1--;
		display_val2--;
		setTimer(100,2);
	}
}
void traffic_state_controller() // Control the traffic light state and update 7Seg Value
{
	if(timer_flag[1])
		{
			switch (traffic_state)
			{
				case 0: // green1 red2
					HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin| red2_Pin, RESET);
					HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin|yellow1_Pin, SET);
					HAL_GPIO_WritePin(green2_GPIO_Port,green2_Pin|yellow2_Pin, SET);
					////////////////////////// green1 red2 ON
					display_val1 = time_green/100;
					display_val2 = time_red/100;
					setTimer(100,2);
					setTimer(time_green,1);
					traffic_state++;
					break;
				case 1:  // yellow1 red2
					HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin|red2_Pin, RESET);
					HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin|green1_Pin, SET);
					HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin|yellow2_Pin, SET);
					////////////////////////// yellow1 red2 ON
					display_val1 = time_yellow/100;
					setTimer(100,2);
					setTimer(time_yellow,1);
					traffic_state++;
					break;
				case 2:  //red1 green2
					HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, RESET);
					HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, RESET);
					HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin|yellow1_Pin, SET);
					HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin|yellow2_Pin, SET);
					////////////////////////// red1 green2 ON
					display_val1 = time_red/100;
					display_val2 = time_green/100;
					setTimer(time_green,1);
					setTimer(100,2);
					traffic_state++;
					break;
				case 3: //red1 yellow2
					HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, RESET);
					HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, RESET);
					HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin|yellow1_Pin|red2_Pin, SET);
					HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, SET);
					////////////////////////// red1 yellow2 ON
					setTimer(100,2);
					setTimer(time_yellow,1);
					display_val2 = time_yellow/100;
					traffic_state=0;
					break;
				default:
					traffic_state=0;
					break;
			}
		}
}
void setting_led_controller(int mode)
{
	if(timer_flag[0])
		{
			switch (led_scan_counter)
			{
				case 0:
					HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, RESET);
					HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en3_Pin|en4_Pin, SET);
					display7Seg(mode/10);
					led_scan_counter++;
					break;
				case 1:
					HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, RESET);
					HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin|en3_Pin|en4_Pin, SET);
					display7Seg(mode%10);
					led_scan_counter++;
					break;
				case 2:
					HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, RESET);
					HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en1_Pin|en4_Pin, SET);
					switch (mode) {
						case 1:
							display7Seg(time_red / 1000);
							break;
						case 2:
							display7Seg(time_yellow / 1000);
							break;
						case 3:
							display7Seg(time_green / 1000);
							break;
						default:
							break;
					}
					led_scan_counter++;
					break;
				case 3:
					HAL_GPIO_WritePin(en4_GPIO_Port, en4_Pin, RESET);
					HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en3_Pin|en1_Pin, SET);
					switch (mode) {
						case 1:
							display7Seg(time_red / 100 %10);
							break;
						case 2:
							display7Seg(time_yellow / 100 %10);
							break;
						case 3:
							display7Seg(time_green / 100 %10);
							break;
						default:
							break;
					}
					led_scan_counter=0;
					break;
				default:
					led_scan_counter=0;
					break;
			}
			setTimer(25,0);
		}
}
void clear_led() // Traffic LED OFF
{
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin|yellow1_Pin|red1_Pin|red2_Pin, SET);
	HAL_GPIO_WritePin(green2_GPIO_Port,green2_Pin|yellow2_Pin, SET);
}
void led_controller() // SCAN The 4 7SEG at speed of 2HZ
{
	if(timer_flag[0])
	{
		switch (led_scan_counter)
		{
			case 0:
				HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, RESET);
				HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en3_Pin|en4_Pin, SET);
				display7Seg(display_val1/10);
				led_scan_counter++;
				break;
			case 1:
				HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, RESET);
				HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin|en3_Pin|en4_Pin, SET);
				display7Seg(display_val1%10);
				led_scan_counter++;
				break;
			case 2:
				HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, RESET);
				HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en1_Pin|en4_Pin, SET);
				display7Seg(display_val2/10);
				led_scan_counter++;
				break;
			case 3:
				HAL_GPIO_WritePin(en4_GPIO_Port, en4_Pin, RESET);
				HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin|en3_Pin|en1_Pin, SET);
				display7Seg(display_val2%10);
				led_scan_counter=0;
				break;
			default:
				led_scan_counter=0;
				break;
		}
		setTimer(25,0);
	}
}
void display7Seg(int decimalVal) // DECIMAL to 7SEG Config Signal
{
	if(decimalVal > 9) decimalVal = 0;
		HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, (decimalVal==1||decimalVal==4) ? SET:RESET);
		HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, (decimalVal==5||decimalVal==6) ? SET:RESET);
		HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, (decimalVal==2) ? SET:RESET);
		HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, (decimalVal==1||decimalVal==4 || decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, (decimalVal==1||decimalVal==4 || decimalVal==3 || decimalVal==5 || decimalVal==7 || decimalVal==9) ? SET:RESET);
		HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, (decimalVal==1||decimalVal==2||decimalVal==3||decimalVal==7) ? SET:RESET);
		HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, (decimalVal==0||decimalVal==1||decimalVal==7) ? SET:RESET);
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
