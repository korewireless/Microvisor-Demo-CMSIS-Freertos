/**
  ******************************************************************************
  * @file    stm32u5xx_hal_sd_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SD HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_SD_EX_H
#define STM32U5xx_HAL_SD_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup SDEx
  * @brief SD HAL extended module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SDEx_Exported_Types SDEx Exported Types
  * @{
  */


/**
  * @}
  */

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* -----------------Linked List Wrapper --------------------------------------*/

#define SD_DMALinkNodeTypeDef        SDMMC_DMALinkNodeTypeDef
#define SD_DMALinkNodeConfTypeDef    SDMMC_DMALinkNodeConfTypeDef
#define SD_DMALinkedListTypeDef      SDMMC_DMALinkedListTypeDef
/* ----------------- Linked Aliases ------------------------------------------*/
#define HAL_SDEx_DMALinkedList_WriteCpltCallback HAL_SD_TxCpltCallback
#define HAL_SDEx_DMALinkedList_ReadCpltCallback  HAL_SD_RxCpltCallback

/* Exported functions --------------------------------------------------------*/
/** @defgroup SDEx_Exported_Functions SDEx Exported Functions
  * @{
  */
/** @defgroup SDEx_Exported_Functions_Group1 Linked List functions
  * @{
  */
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_ReadBlocks (SD_HandleTypeDef *hsd,SD_DMALinkedListTypeDef * pLinkedList, uint32_t BlockAdd, uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_WriteBlocks (SD_HandleTypeDef *hsd,SD_DMALinkedListTypeDef * pLinkedList, uint32_t BlockAdd, uint32_t NumberOfBlocks);

HAL_StatusTypeDef HAL_SDEx_DMALinkedList_BuildNode(SD_DMALinkNodeTypeDef * pNode, SD_DMALinkNodeConfTypeDef * pNodeConf);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_InsertNode(SD_DMALinkedListTypeDef * pLinkedList, SD_DMALinkNodeTypeDef * pPrevNode,SD_DMALinkNodeTypeDef * pNewNode);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_RemoveNode(SD_DMALinkedListTypeDef * pLinkedList,SD_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_LockNode(SD_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_UnlockNode(SD_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_EnableCircularMode(SD_DMALinkedListTypeDef * pLinkedList);
HAL_StatusTypeDef HAL_SDEx_DMALinkedList_DisableCircularMode(SD_DMALinkedListTypeDef * pLinkedList);

void HAL_SDEx_Read_DMALnkLstBufCpltCallback(SD_HandleTypeDef *hsd);
void HAL_SDEx_Write_DMALnkLstBufCpltCallback(SD_HandleTypeDef *hsd);


/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions prototypes ----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif


#endif /* stm32u5xx_HAL_SD_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
