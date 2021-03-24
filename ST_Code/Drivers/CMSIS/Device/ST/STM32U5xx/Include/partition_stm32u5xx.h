/**
  ******************************************************************************
  * @file    partition_stm32u5xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32U5xx Device Header File for Initial Setup for
  *          Secure / Non-Secure Zones based on CMSIS CORE V5.4.0
  *
  *          The file is included in system_stm32u5xx_s.c in secure application.
  *          It includes the configuration section that allows to select the
  *          STM32U5xx device partitioning file for system core secure attributes
  *          and interrupt secure and non-secure assignment.
  *
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32u5xx
  * @{
  */

#ifndef PARTITION_STM32U5XX_H
#define PARTITION_STM32U5XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Secure_configuration_section
  * @{
  */

#if defined(STM32U575xx)
  #include "partition_stm32u575xx.h"
#elif defined(STM32U585xx)
  #include "partition_stm32u585xx.h"
#else
  #error "Please select first the target STM32U5xx device used in your application (in stm32u5xx.h file)"
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PARTITION_STM32U5XX_H */
/**
  * @}
  */

/**
  * @}
  */




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
