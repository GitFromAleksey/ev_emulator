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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint32_t PortValue;
} t_di;

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint32_t PortValue;	
} t_do;

typedef enum
{
	EV_READY,
	EV_ERROR,
	EV_WARNING,
	EV_NONE
} t_ev_status;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
t_ev_status EV_STATUS = EV_NONE;

t_do DoLedStatus;
t_do DoV_S2_Out;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const char * uart_str = "EV Emulator start\n";
void SendMessage(uint8_t *msg, uint16_t len)
{
	HAL_UART_Transmit(&huart3, msg, len,100);
}


// ---------------------------------------------------------------------------
void DO_Switch(t_do *dout, bool set)
{
	if(set) 
		LL_GPIO_ResetOutputPin(dout->GPIOx, dout->PortValue);
	else
		LL_GPIO_SetOutputPin(dout->GPIOx, dout->PortValue);
}
void DO_Toggle(t_do *dout)
{
	LL_GPIO_TogglePin(dout->GPIOx, dout->PortValue);
}
bool DI_GetState(t_di *din)
{
	return ( 0 != LL_GPIO_IsInputPinSet(din->GPIOx, din->PortValue));
}
bool DO_GetState(t_di *dout)
{
	return ( 0 != LL_GPIO_IsInputPinSet(dout->GPIOx, dout->PortValue));
}
void LedStatusSwitch(bool set)
{
	DO_Switch(&DoLedStatus, set);
}
void VS2OutSwitch(bool set)
{
	DO_Switch(&DoV_S2_Out, set);
}
void LedStatusHandler(void)
{
	#define DEFAULT_DELAY    1000u
	static uint32_t prev_time_ms = 0;
	uint16_t period = DEFAULT_DELAY;
	uint16_t delay = DEFAULT_DELAY>>1;
	uint32_t time_delta = HAL_GetTick() - prev_time_ms;
	
	switch((int)EV_STATUS)
	{
		case EV_READY:
			break;
		case EV_ERROR:
			break;
		case EV_WARNING:
			break;
		case EV_NONE:
//			delay = 500;
			break;
		default:
			break;
	}
	
	if( time_delta > period)
	{
		prev_time_ms = HAL_GetTick();
		LedStatusSwitch(true);
	}
	else if( time_delta > delay)
	{
		LedStatusSwitch(false);
	}

}
// ---------------------------------------------------------------------------
volatile uint16_t adc0_in = 0;
volatile uint16_t adc0_voltage = 0;
volatile uint16_t adc1_in = 0;

#define FILTR_DEPTH    4u


uint16_t AdcFiltr(uint16_t data)
{
	static uint32_t accum = 0;
	
	accum -= accum>>FILTR_DEPTH;
	accum += data;
	
	return (uint16_t)(accum>>FILTR_DEPTH);
}

#define ADC_RESOLUTION    4095
#define MAX_INPUT_VOLTAGE (3.3f) * 1000
#define COEF    (MAX_INPUT_VOLTAGE/ADC_RESOLUTION)
#define COEF_FP (uint32_t)(COEF * 0xFFFF)

uint16_t AdcToVoltageCalc(uint16_t adc_data)
{
	uint16_t result = 0;
	uint32_t temp = adc_data;

	temp = COEF_FP * temp;
	temp = temp>>16;
	result = temp;
	
	return result;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
	{
		adc0_in = HAL_ADC_GetValue(hadc);
		adc0_in = AdcFiltr(adc0_in);
		adc0_voltage = AdcToVoltageCalc(adc0_in);
////		HAL_ADC_Start_IT(hadc);
		HAL_ADC_Start_IT(&hadc1);
		DO_Toggle(&DoV_S2_Out);
	}
}
// ---------------------------------------------------------------------------
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
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	HAL_ADC_Start_IT(&hadc1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	DoLedStatus.GPIOx = LED_STATUS_GPIO_Port;
	DoLedStatus.PortValue = LED_STATUS_Pin;
	
	DoV_S2_Out.GPIOx = V_S2_OUT_GPIO_Port;
	DoV_S2_Out.PortValue = V_S2_OUT_Pin;
	
	SendMessage((uint8_t*)uart_str, 18);
	EV_STATUS = EV_NONE;
	
  while (1)
  {
//		HAL_Delay(500);
//		DO_Toggle(&DoLedStatus);
		LedStatusHandler();
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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(72000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_8);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

  /**/
  LL_GPIO_ResetOutputPin(V_S2_OUT_GPIO_Port, V_S2_OUT_Pin);

  /**/
  GPIO_InitStruct.Pin = LED_STATUS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(LED_STATUS_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = V_S2_OUT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(V_S2_OUT_GPIO_Port, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
