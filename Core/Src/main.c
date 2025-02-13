/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "cordic.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//TEST PARA

float theta=0;
//TEST PARA
#include "stdio.h"
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,10);
	return ch;
}

#include "SVPWM.h"
#include "Cordic_.h"
#include "math.h"
#include "arm_math.h"
#include "MT6816.h"
#include "SMO.h"
#include "tim.h"
#include "BLDC.h"



uint8_t flag_cmd=0;
uint16_t SetVal=0;

uint16_t adcval[3]={0};
void ADC_Calibration(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1 , ADC_SINGLE_ENDED);    //AD校准
	//while (HAL_ADCEx_Calibration_GetState(&hadc) != HAL_ADC_CALIBRATION_STATE_COMPLETED);//等校准
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim1)
	{
		HAL_GPIO_TogglePin(GPIOC , GPIO_PIN_14);
		//ADC
		HAL_ADC_Start(&hadc1);
		HAL_ADC_Start(&hadc2);
		while(!(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC));
		while(!(HAL_ADC_GetState(&hadc2), HAL_ADC_STATE_REG_EOC));

		//MT6816
		getmagval=MT6816_ReadVal();		
	}		
}

//SVPWM



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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_TIM1_Init();
  MX_SPI2_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_USART2_UART_Init();
  MX_CORDIC_Init();
  /* USER CODE BEGIN 2 */
	
	
	
//	HAL_TIM_Base_Start_IT(&htim1);
//	__HAL_TIM_SetCompare(&htim1,    TIM_CHANNEL_4   , 8500-1);
//		HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_4);	
		

//INIT
		InitCordic();
		InitBLDC(&ThisBLDC);
		Init_SMO(&ThisS , 5.f/8.f*0.4 , 5.f/8.f*0.4 , 5 , 1);
		
		//InitcompIq_calibration(&ThisBLDC , &ThisIqComp);		
		//compIq_calibration(&ThisBLDC , &ThisIqComp);

		 //ThisBLDC.w_mecexp=-3.14159;
		//Init_SMO(&ThisS , 0.00005f/0.00008f*0.4 , 0.00005f/0.00008f*0.4 , 5 , 1);
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA , GPIO_PIN_4 , GPIO_PIN_SET);
		theta=angleanaloging(theta);
//		compIq_calibration(&ThisBLDC , &ThisIqComp);
//		Org_E_Calibration(flag_cmd , SetVal);
//		SV_PWM_Cal(&ThisSV , 4 , 0, 10 , sinf(theta) , cosf(theta)  );
//		printf("%.4f\n", ThisBLDC.Id);
	//	printf("%.4f,%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n" , ThisBLDC.theta , ThisBLDC.raw_angle  ,  ThisBLDC.fil_thetaE , ThisBLDC.thetaE , ThisBLDC.w_mec , \
					ThisBLDC.Ia, ThisBLDC.sinthetaE ,ThisBLDC.costhetaE);
//    printf("%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n" , ThisSV.Ta , ThisSV.Tb ,  ThisBLDC.delta_theta ,ThisBLDC.theta ,ThisBLDC.thetaE,ThisBLDC.w_mec , ThisBLDC.sinthetaE, ThisBLDC.costhetaE );
    printf("%d,%d,%d,%d,%.4f,%.4f,%.4f,%.4f\n" , ThisBLDC.exppos , ThisBLDC.thiserr_pos ,  ThisBLDC.raw_angle_buffer ,ThisBLDC.averposerr ,ThisBLDC.thetaE,ThisBLDC.w_mec , ThisBLDC.sinthetaE, ThisBLDC.costhetaE );


 		HAL_GPIO_WritePin(GPIOA , GPIO_PIN_4 , GPIO_PIN_RESET);  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
