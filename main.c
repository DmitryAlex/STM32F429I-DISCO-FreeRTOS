/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"
#include "freeRTOS.h"
#include "freeRTOSConfig.h"
#include "task.h"

/*----------------------------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/*----------------------------------------------------------------------------*/
void vTask1(void *pvParameters)
{
  for(;;)
  {
    GPIO_SetBits(GPIOG, GPIO_Pin_13);
    vTaskDelay(200);
    GPIO_ResetBits(GPIOG, GPIO_Pin_13);
    vTaskDelay(500);
  }
}
/*----------------------------------------------------------------------------*/
void vTask2(void *pvParameters)
{
  for(;;)
  {
    GPIO_SetBits(GPIOG, GPIO_Pin_14);
    vTaskDelay(1000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_14);
    vTaskDelay(1000);
  }
}
/*----------------------------------------------------------------------------*/
int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
  
  xTaskCreate( &vTask1, "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
              ( xTaskHandle * ) NULL);
  xTaskCreate( &vTask2, "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
              ( xTaskHandle * ) NULL);
  
  vTaskStartScheduler();
  while(1);
}
/*----------------------------------------------------------------------------*/
void vApplicationTickHook(void){}
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){}
void vApplicationIdleHook(void){}
void vApplicationMallocFailedHook(void){}
/*----------------------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
