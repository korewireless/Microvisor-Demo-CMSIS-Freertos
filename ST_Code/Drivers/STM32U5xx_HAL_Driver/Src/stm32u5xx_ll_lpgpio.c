/**
  ******************************************************************************
  * @file    stm32u5xx_ll_lpgpio.c
  * @author  MCD Application Team
  * @brief   LPGPIO LL module driver.
  *****************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_bus.h"
#include "stm32u5xx_ll_lpgpio.h"
#ifdef  USE_FULL_ASSERT
#include "stm32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (LPGPIO)

/** @addtogroup LPGPIO_LL
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPGPIO_LL_Private_Macros
  * @{
  */
#define IS_LL_LPGPIO_PIN(__VALUE__)          (((0x00000000U) < (__VALUE__)) && ((__VALUE__) <= (LL_LPGPIO_PIN_ALL)))

#define IS_LL_LPGPIO_MODE(__VALUE__)         (((__VALUE__) == LL_LPGPIO_MODE_INPUT)     ||\
                                              ((__VALUE__) == LL_LPGPIO_MODE_OUTPUT))

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPGPIO_LL_Exported_Functions
  * @{
  */

/** @addtogroup LPGPIO_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize LPGPIO registers (Registers restored to their default values).
  * @param  LPGPIOx LPGPIO Port
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPGPIO registers are de-initialized
  *          - ERROR:   Wrong LPGPIO Port
  */
ErrorStatus LL_LPGPIO_DeInit(GPIO_TypeDef *LPGPIOx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_LPGPIO_ALL_INSTANCE(LPGPIOx));

  /* Force and Release reset on clock of LPGPIOx Port */
  if (LPGPIOx == LPGPIO)
  {
    LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
    LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_LPGPIO1);
  }
  else
  {
    status = ERROR;
  }

  return (status);
}

/**
  * @brief  Initialize LPGPIO registers according to the specified parameters in LPGPIO_InitStruct.
  * @param  LPGPIOx LPGPIO Port
  * @param  LPGPIO_InitStruct: pointer to a @ref LL_LPGPIO_InitTypeDef structure
  *         that contains the configuration information for the specified LPGPIO peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPGPIO registers are initialized according to LPGPIO_InitStruct content
  *          - ERROR:   Not applicable
  */
ErrorStatus LL_LPGPIO_Init(GPIO_TypeDef *LPGPIOx, LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct)
{
  uint32_t pinpos     = 0x00000000U;
  uint32_t currentpin = 0x00000000U;

  /* Check the parameters */
  assert_param(IS_LPGPIO_ALL_INSTANCE(LPGPIOx));
  assert_param(IS_LL_LPGPIO_PIN(LPGPIO_InitStruct->Pin));
  assert_param(IS_LL_LPGPIO_MODE(LPGPIO_InitStruct->Mode));

  /* ------------------------- Configure the port pins ---------------- */
  /* Initialize  pinpos on first pin set */
  pinpos = POSITION_VAL(LPGPIO_InitStruct->Pin);

    /* Configure the port pins */
  while (((LPGPIO_InitStruct->Pin) >> pinpos) != 0x00000000U)
  {
  /* Get current io position */
  currentpin = (LPGPIO_InitStruct->Pin) & (0x00000001UL << pinpos);

  if (currentpin)
  {
    /* Pin Mode configuration */
    LL_LPGPIO_SetPinMode(LPGPIOx, currentpin, LPGPIO_InitStruct->Mode);
  }
  pinpos++;
  }
  return (SUCCESS);
}

/**
  * @brief Set each @ref LL_LPGPIO_InitTypeDef field to default value.
  * @param LPGPIO_InitStruct: pointer to a @ref LL_LPGPIO_InitTypeDef structure
  *                           whose fields will be set to default values.
  * @retval None
  */

void LL_LPGPIO_StructInit(LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct)
{
  /* Reset LPGPIO init structure parameters values */
  LPGPIO_InitStruct->Pin        = LL_LPGPIO_PIN_ALL;
  LPGPIO_InitStruct->Mode       = LL_LPGPIO_MODE_OUTPUT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (LPGPIO) */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
