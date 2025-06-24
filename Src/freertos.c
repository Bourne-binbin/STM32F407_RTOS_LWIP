/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern char RxBuffer[256];   //接收数据
extern uint8_t aRxBuffer;			//接收中断缓冲
extern uint8_t Uart3_Rx_Cnt;		//接收缓冲计数
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId SCIHandle;
osThreadId NETHandle;
osThreadId LEDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void SCI_FUNC(void const * argument);
void NET_FUNC(void const * argument);
void LED_FUNC(void const * argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

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
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of SCI */
  osThreadDef(SCI, SCI_FUNC, osPriorityRealtime, 0, 256);
  SCIHandle = osThreadCreate(osThread(SCI), NULL);

  /* definition and creation of NET */
  osThreadDef(NET, NET_FUNC, osPriorityRealtime, 0, 256);
  NETHandle = osThreadCreate(osThread(NET), NULL);

  /* definition and creation of LED */
  osThreadDef(LED, LED_FUNC, osPriorityLow, 0, 128);
  LEDHandle = osThreadCreate(osThread(LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_SCI_FUNC */
/**
* @brief Function implementing the SCI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SCI_FUNC */
void SCI_FUNC(void const * argument)
{
    
                 
  /* init code for LWIP */
  MX_LWIP_Init();

  /* USER CODE BEGIN SCI_FUNC */
  /* Infinite loop */
  for(;;)
  {
//    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
//    printf("SCI任务通知获取成功!\n");
//		HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer, 1);
//		printf("aRxBuffer = %d\n", aRxBuffer);
//	 if(Uart3_Rx_Cnt >= 255)  //溢出判断
//	 {
//	  Uart3_Rx_Cnt = 0;
//	  memset(RxBuffer,0x00,sizeof(RxBuffer));
//	  HAL_UART_Transmit(&huart3, (uint8_t *)"数据溢出", 10,0xFFFF); 	
//	 }
//	 else
//	 {
//	  RxBuffer[Uart3_Rx_Cnt++] = aRxBuffer;   //接收数据转存

//	  if((RxBuffer[Uart3_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart3_Rx_Cnt-2] == 0x0D)) //判断结束位
//	  {
//	 	 printf("板子发出:\n");
//	 	 HAL_UART_Transmit(&huart3, (uint8_t *)&RxBuffer, Uart3_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//	 				 while(HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
//	 	 Uart3_Rx_Cnt = 0;
//	 	 memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
//	  }
//	 }
		 osDelay(1);
	}
  /* USER CODE END SCI_FUNC */
}

/* USER CODE BEGIN Header_NET_FUNC */
/**
* @brief Function implementing the NET thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_NET_FUNC */
void NET_FUNC(void const * argument)
{
  /* USER CODE BEGIN NET_FUNC */
  /* Infinite loop */
  for(;;)
  {
//    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    osDelay(1);
  }
  /* USER CODE END NET_FUNC */
}

/* USER CODE BEGIN Header_LED_FUNC */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_FUNC */
void LED_FUNC(void const * argument)
{
  /* USER CODE BEGIN LED_FUNC */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
    osDelay(1000);
  }
  /* USER CODE END LED_FUNC */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
