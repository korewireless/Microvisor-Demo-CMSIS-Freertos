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
#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"
#include "logging.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define DC_CLK_ENABLE_MACRO   __HAL_RCC_GPIOF_CLK_ENABLE
#define DC_GPIO_Port          GPIOF
#define DC_Pin                GPIO_PIN_13

#define RST_CLK_ENABLE_MACRO  __HAL_RCC_GPIOD_CLK_ENABLE
#define RST_GPIO_Port         GPIOD
#define RST_Pin               GPIO_PIN_10

#define CS_CLK_ENABLE_MACRO   __HAL_RCC_GPIOE_CLK_ENABLE
#define CS_GPIO_Port          GPIOE
#define CS_Pin                GPIO_PIN_12

#define BL_CLK_ENABLE_MACRO   __HAL_RCC_GPIOD_CLK_ENABLE
#define BL_GPIO_Port          GPIOD
#define BL_Pin                GPIO_PIN_13

#define SPI_CLK_ENABLE_MACRO __HAL_RCC_GPIOE_CLK_ENABLE
#define SPI_GPIO_Port        GPIOE
#define SPI_SCK_Pin          GPIO_PIN_13
#define SPI_SDO_Pin          GPIO_PIN_15
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
