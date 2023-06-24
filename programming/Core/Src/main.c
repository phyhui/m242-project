/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "LED_Treiber.h"
#include "Taster_Treiber.h"
#include "Seg_Driver.h"

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
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for tasterTask */
osThreadId_t tasterTaskHandle;
const osThreadAttr_t tasterTask_attributes = {
  .name = "tasterTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for displayTask */
osThreadId_t displayTaskHandle;
const osThreadAttr_t displayTask_attributes = {
  .name = "displayTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for stopwatchTimer */
osTimerId_t stopwatchTimerHandle;
const osTimerAttr_t stopwatchTimer_attributes = {
  .name = "stopwatchTimer"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
void StartDefaultTask(void *argument);
void Taster_Treiber_Task(void *argument);
void StartDisplayTask(void *argument);
//void stopwatchCallback(void *argument);

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
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of stopwatchTimer */
  //stopwatchTimerHandle = osTimerNew(stopwatchCallback, osTimerPeriodic, NULL, &stopwatchTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of tasterTask */
  tasterTaskHandle = osThreadNew(Taster_Treiber_Task, NULL, &tasterTask_attributes);

  /* creation of displayTask */
  displayTaskHandle = osThreadNew(StartDisplayTask, NULL, &displayTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_TIM34;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Tim34ClockSelection = RCC_TIM34CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 36000-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 250;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_1_Pin|LED_2_Pin|LED_3_Pin|OUT_7SEG_SFTCLK_Pin
                          |OUT_7SEG_SDI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, OUT_Buzzer_Pin|OUT_7SEGLCHCLK_Pin|LED_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TASTER_1_Pin TASTER_2_Pin */
  GPIO_InitStruct.Pin = TASTER_1_Pin|TASTER_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_1_Pin LED_2_Pin LED_3_Pin OUT_7SEG_SFTCLK_Pin
                           OUT_7SEG_SDI_Pin */
  GPIO_InitStruct.Pin = LED_1_Pin|LED_2_Pin|LED_3_Pin|OUT_7SEG_SFTCLK_Pin
                          |OUT_7SEG_SDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : TASTER_3_Pin */
  GPIO_InitStruct.Pin = TASTER_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TASTER_3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OUT_Buzzer_Pin OUT_7SEGLCHCLK_Pin LED_4_Pin */
  GPIO_InitStruct.Pin = OUT_Buzzer_Pin|OUT_7SEGLCHCLK_Pin|LED_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int stopuhr = 0;
int timerStatus = 10;
int timer = 0;
int meanTime = 0;
int mode = 0;
int stopuhrIsRuning = 0;
int timerIsRunning = 0;
int taster3Counter = 0;
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  HAL_GPIO_TogglePin(OUT_Buzzer_GPIO_Port, OUT_Buzzer_Pin);

  LED_Set(LED_1, 0);
  LED_Set(LED_2, 0);
  LED_Set(LED_3, 0);
  LED_Set(LED_4, 1);
  /* Infinite loop */
  while(1)
  {
	  while(mode == 0){
		  LED_Set(LED_2, 0);
		  LED_Set(LED_1, 1);
		  if(Taster_Get(TASTER_3)){
			  switchMode();
			  if(mode != 1){
				  stopuhr = 0;
				  SEG_Driver_Write(stopuhr, SEG_Driver_DP_2 | SEG_Driver_DP_4,0);
			  }
		  }
		  if(Taster_Get(TASTER_1)){
			  beep(100);
			  stopuhrIsRuning = 1;
			  LED_Set(LED_3, 1);
		  }
		  while(stopuhrIsRuning == 1 && mode == 0){
			  stopuhrRunning();
		  }
		  osDelay(100);
		  countDownTimer();
	  }
	  while(mode == 1){
		  LED_Set(LED_1, 0);
		  LED_Set(LED_2, 1);
		  while(timerStatus != 1990){
			  if(Taster_Get(TASTER_1)){
				  timer = timer - timerStatus;
			  }
			  if(Taster_Get(TASTER_2)){
				  timer = timer + timerStatus;
			  }
			  if(Taster_Get(TASTER_3)){
				  timerStatus = timerStatus + 990;
			  }
			  SEG_Driver_Write(timer, SEG_Driver_DP_2 | SEG_Driver_DP_4,SEG_Driver_FLASH_SLOW);
			  countUpStopuhr();
			  osDelay(100);
		  }
		  timerIsRunning = 1;
		  SEG_Driver_Write(timer, SEG_Driver_DP_2 | SEG_Driver_DP_4,0);
		  osDelay(100);
		  countUpStopuhr();
		  countDownTimer();
		  switchMode();
	  }
    osDelay(100);
  }
}

void beep(int time){
	HAL_GPIO_TogglePin(OUT_Buzzer_GPIO_Port, OUT_Buzzer_Pin);
	osDelay(time);
	HAL_GPIO_TogglePin(OUT_Buzzer_GPIO_Port, OUT_Buzzer_Pin);
}

void countDownTimer(){
	if(timer == 0 && timerIsRunning == 1){
	  timerStatus = 10;
	  timerIsRunning = 0;
	  beep(3000);
	}
	if(timerIsRunning == 1){
		if(timer % 1000 == 0){
			  timer -= 400;
		}
		else{
			timer--;
		}
	}
}

void countUpStopuhr(){
	 if(stopuhrIsRuning == 1){
		  if((stopuhr + 400) % 1000 == 0){
			  stopuhr += 400;
		  }
		  else{
			  stopuhr++;
		  }
	  }
}

void stopuhrRunning(){
	if(Taster_Get(TASTER_2) && mode == 0){
		beep(100);
		stopuhrIsRuning = 0;
		LED_Set(LED_3, 0);
	}
	if(Taster_Get(TASTER_3) && mode == 0){
	  switchMode();
	  if( mode != 1 && meanTime == 0){
		  beep(100);
		  meanTime = stopuhr;
	  }
	  else{
		  beep(100);
		  meanTime = 0;
	  }
   }
   osDelay(100);
   countUpStopuhr();
   countDownTimer();
   if(meanTime == 0 && mode == 0){
	   SEG_Driver_Write(stopuhr, SEG_Driver_DP_2 | SEG_Driver_DP_4,0);
   }
   else if(mode == 0){
	   SEG_Driver_Write(meanTime, SEG_Driver_DP_2 | SEG_Driver_DP_4, SEG_Driver_FLASH_SLOW);
   }
}

void switchMode(){
	while(Taster_Get(TASTER_3)){
		  taster3Counter++;
		  if(taster3Counter > 10){
			  if(mode == 0){
				  mode = 1;
				  SEG_Driver_Write(timer, SEG_Driver_DP_2 | SEG_Driver_DP_4, SEG_Driver_FLASH_SLOW);
			  }
			  else{
				  mode = 0;
				  SEG_Driver_Write(stopuhr, SEG_Driver_DP_2 | SEG_Driver_DP_4, 0);
			  }
			  taster3Counter = 0;
		  }
		  osDelay(100);
	  }
}

/* USER CODE END 5 */

/* USER CODE BEGIN Header_Taster_Treiber_Task */
/**
* @brief Function implementing the tasterTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Taster_Treiber_Task */
void Taster_Treiber_Task(void *argument)
{
  /* USER CODE BEGIN Taster_Treiber_Task */
  /* Infinite loop */
	Taster_Treiber_Init_Task(argument);
  /* USER CODE END Taster_Treiber_Task */
}

/* USER CODE BEGIN Header_StartDisplayTask */
/**
* @brief Function implementing the displayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDisplayTask */
void StartDisplayTask(void *argument)
{
  /* USER CODE BEGIN StartDisplayTask */
  /* Infinite loop */
	while(true){
	      SEG_Driver_Task_5ms();
	      osDelay(5);
	  }
  /* USER CODE END StartDisplayTask */
}

/* stopwatchCallback function */
void stopwatchCallback(void *argument)
{
  /* USER CODE BEGIN stopwatchCallback */

  /* USER CODE END stopwatchCallback */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
