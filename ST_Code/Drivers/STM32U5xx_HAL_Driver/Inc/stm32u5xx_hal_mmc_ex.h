/**
  ******************************************************************************
  * @file    stm32u5xx_hal_mmc_ex.h
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
#ifndef STM32U5xx_HAL_MMC_EX_H
#define STM32U5xx_HAL_MMC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup MMCEx
  * @brief SD HAL extended module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup MMCEx_Exported_Types MMCEx Exported Types
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

#define MMC_DMALinkNodeTypeDef        SDMMC_DMALinkNodeTypeDef
#define MMC_DMALinkNodeConfTypeDef    SDMMC_DMALinkNodeConfTypeDef
#define MMC_DMALinkedListTypeDef      SDMMC_DMALinkedListTypeDef
/* ----------------- Linked Aliases ------------------------------------------*/
#define HAL_MMCx_DMALinkedList_WriteCpltCallback HAL_MMC_TxCpltCallback
#define HAL_MMCx_DMALinkedList_ReadCpltCallback  HAL_MMC_RxCpltCallback

/* Exported functions --------------------------------------------------------*/
/** @defgroup MMCEx_Exported_Functions MMCEx Exported Functions
  * @{
  */

/** @defgroup MMCEx_Exported_Functions_Group1 MultiBuffer functions
  * @{
  */
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_ReadBlocks (MMC_HandleTypeDef *hmmc,SDMMC_DMALinkedListTypeDef * pLinkedList, uint32_t BlockAdd, uint32_t NumberOfBlocks);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_WriteBlocks (MMC_HandleTypeDef *hmmc,SDMMC_DMALinkedListTypeDef * pLinkedList, uint32_t BlockAdd, uint32_t NumberOfBlocks);

HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_BuildNode(MMC_DMALinkNodeTypeDef * pNode, MMC_DMALinkNodeConfTypeDef * pNodeConf);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_InsertNode(MMC_DMALinkedListTypeDef * pLinkedList, MMC_DMALinkNodeTypeDef * pPrevNode,MMC_DMALinkNodeTypeDef * pNewNode);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_RemoveNode(MMC_DMALinkedListTypeDef * pLinkedList,MMC_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_LockNode(MMC_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_UnlockNode(MMC_DMALinkNodeTypeDef * pNode);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_EnableCircularMode(SDMMC_DMALinkedListTypeDef * pLinkedList);
HAL_StatusTypeDef HAL_MMCEx_DMALinkedList_DisableCircularMode(SDMMC_DMALinkedListTypeDef * pLinkedList);

void HAL_MMCEx_Read_DMALnkLstBufCpltCallback(MMC_HandleTypeDef *hmmc);
void HAL_MMCEx_Write_DMALnkLstBufCpltCallback(MMC_HandleTypeDef *hmmc);


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


#endif /* STM32U5xx_HAL_MMCEx_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
