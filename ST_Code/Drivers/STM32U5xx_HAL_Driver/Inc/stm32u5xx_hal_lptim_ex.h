/**
  ******************************************************************************
  * @file    stm32u5xx_hal_lptim_ex.h
  * @author  MCD Application Team
  * @brief   Header file of LPTIM Extended HAL module.
  ******************************************************************************
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_LPTIM_EX_H
#define STM32U5xx_HAL_LPTIM_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @defgroup LPTIMEx LPTIMEx
  * @{
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup LPTIMEx_Private_Macros LPTIMEx Private Macros
  * @{
  */

/******************* LPTIM Instances : output(s) available **********************/
#define IS_LPTIM_CCX_INSTANCE(__INSTANCE__, __CHANNEL__) \
  (((((__INSTANCE__) == LPTIM1_NS)  || ((__INSTANCE__) == LPTIM1_S))  && \
    (((__CHANNEL__)  == LPTIM_CHANNEL_1) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_2) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_ALL))) \
   ||                                        \
   ((((__INSTANCE__) == LPTIM2_NS)  || ((__INSTANCE__) == LPTIM2_S))  && \
    (((__CHANNEL__)  == LPTIM_CHANNEL_1) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_2) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_ALL))) \
   ||                                        \
   ((((__INSTANCE__) == LPTIM3_NS)  || ((__INSTANCE__) == LPTIM3_S))  && \
    (((__CHANNEL__)  == LPTIM_CHANNEL_1) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_2) ||  \
     ((__CHANNEL__)  == LPTIM_CHANNEL_ALL))) \
   ||                                        \
   ((((__INSTANCE__) == LPTIM4_NS)  || ((__INSTANCE__) == LPTIM4_S))  && \
    ((__CHANNEL__)  == LPTIM_CHANNEL_1)))
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_HAL_LPTIM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

