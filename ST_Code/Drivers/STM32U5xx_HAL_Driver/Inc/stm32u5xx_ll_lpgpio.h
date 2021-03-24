/**
  ******************************************************************************
  * @file    stm32u5xx_ll_lpgpio.h
  * @author  MCD Application Team
  * @brief   Header file of LPGPIO LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_LL_LPGPIO_H
#define STM32U5xx_LL_LPGPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined (LPGPIO)

/** @defgroup LPGPIO_LL LPGPIO
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LPGPIO_LL_Private_Macros LPGPIO Private Macros
  * @{
  */

/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup LPGPIO_LL_ES_INIT LPGPIO Exported Init structures
  * @{
  */

/**
  * @brief LL LPGPIO Init Structure definition
  */
typedef struct
{
  uint32_t Pin;          /*!< Specifies the LPGPIO pins to be configured.
                              This parameter can be any value of @ref LPGPIO_LL_EC_PIN */

  uint32_t Mode;         /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref LPGPIO_LL_EC_MODE.*/

}LL_LPGPIO_InitTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Constants LPGPIO Exported Constants
  * @{
  */

/** @defgroup LPGPIO_pins LPGPIO pins
  * @{
  */
#define LL_LPGPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define LL_LPGPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define LL_LPGPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define LL_LPGPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define LL_LPGPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define LL_LPGPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define LL_LPGPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define LL_LPGPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define LL_LPGPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define LL_LPGPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define LL_LPGPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define LL_LPGPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define LL_LPGPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define LL_LPGPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define LL_LPGPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define LL_LPGPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define LL_LPGPIO_PIN_ALL               ((uint16_t)0xFFFF)  /* All pins selected */

#define LL_LPGPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* PIN mask for assert test */
/**
  * @}
  */

/** @defgroup LPGPIO_LL_EC_MODE Mode
  * @{
  */
#define LL_LPGPIO_MODE_INPUT                 (0x00000000U) /*!< Select input mode */
#define LL_LPGPIO_MODE_OUTPUT                LPGPIO_MODER_MOD0  /*!< Select output mode */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Macros LPGPIO Exported Macros
  * @{
  */

/** @defgroup LPGPIO_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in LPGPIO register
  * @param  __INSTANCE__ LPGPIO Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_LPGPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in LPGPIO register
  * @param  __INSTANCE__ LPGPIO Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_LPGPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup LPGPIO_LL_Exported_Functions LPGPIO Exported Functions
  * @{
  */

/** @defgroup LPGPIO_LL_EF_Port_Configuration Port Configuration
  * @{
  */

/**
  * @brief  Configure lpgpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_LPGPIO_SetPinMode
  * @param  LPGPIOx LPGPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_MODE_INPUT
  *         @arg @ref LL_LPGPIO_MODE_OUTPUT
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_SetPinMode(GPIO_TypeDef *LPGPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(LPGPIOx->MODER, (LPGPIO_MODER_MOD0 << (POSITION_VAL(Pin))), (Mode << (POSITION_VAL(Pin) )));
}

/**
  * @brief  Return lpgpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         LL_LPGPIO_GetPinMode
  * @param  LPGPIOx LPGPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_LPGPIO_MODE_INPUT
  *         @arg @ref LL_LPGPIO_MODE_OUTPUT
  */
__STATIC_INLINE uint32_t LL_LPGPIO_GetPinMode(GPIO_TypeDef *LPGPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(LPGPIOx->MODER,
                             (LPGPIO_MODER_MOD0 << (POSITION_VAL(Pin) ))) >> (POSITION_VAL(Pin) ));
}


/** @defgroup LPGPIO_LL_EF_Data_Access Data Access
  * @{
  */

/**
  * @brief  Return full input data register value for a dedicated port.
  * @rmtoll IDR          IDy           LL_LPGPIO_ReadInputPort
  * @param  LPGPIOx LPGPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t LL_LPGPIO_ReadInputPort(GPIO_TypeDef *LPGPIOx)
{
  return (uint32_t)(READ_REG(LPGPIOx->IDR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           LL_LPGPIO_IsInputPinSet
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPGPIO_IsInputPinSet(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  return (READ_BIT(LPGPIOx->IDR, PinMask) == (PinMask));
}

/**
  * @brief  Write output data register for the port.
  * @rmtoll ODR          ODy           LL_LPGPIO_WriteOutputPort
  * @param  LPGPIOx LPGPIO Port
  * @param  PortValue Level value for each pin of the port
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_WriteOutputPort(GPIO_TypeDef *LPGPIOx, uint32_t PortValue)
{
  WRITE_REG(LPGPIOx->ODR, PortValue);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @rmtoll ODR          ODy           LL_LPGPIO_ReadOutputPort
  * @param  LPGPIOx LPGPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t LL_LPGPIO_ReadOutputPort(GPIO_TypeDef *LPGPIOx)
{
  return (uint32_t)(READ_REG(LPGPIOx->ODR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll ODR          ODy           LL_LPGPIO_IsOutputPinSet
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_LPGPIO_IsOutputPinSet(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  return (READ_BIT(LPGPIOx->ODR, PinMask) == (PinMask));
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @rmtoll BSRR         BSy           LL_LPGPIO_SetOutputPin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_SetOutputPin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->BSRR, PinMask);
}

/**
  * @brief  Set several pins to low level on dedicated gpio port.
  * @rmtoll BRR          BRy           LL_LPGPIO_ResetOutputPin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_ResetOutputPin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->BRR, PinMask);
}

/**
  * @brief  Toggle data value for several pin of dedicated port.
  * @rmtoll ODR          ODy           LL_LPGPIO_TogglePin
  * @param  LPGPIOx LPGPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref LL_LPGPIO_PIN_0
  *         @arg @ref LL_LPGPIO_PIN_1
  *         @arg @ref LL_LPGPIO_PIN_2
  *         @arg @ref LL_LPGPIO_PIN_3
  *         @arg @ref LL_LPGPIO_PIN_4
  *         @arg @ref LL_LPGPIO_PIN_5
  *         @arg @ref LL_LPGPIO_PIN_6
  *         @arg @ref LL_LPGPIO_PIN_7
  *         @arg @ref LL_LPGPIO_PIN_8
  *         @arg @ref LL_LPGPIO_PIN_9
  *         @arg @ref LL_LPGPIO_PIN_10
  *         @arg @ref LL_LPGPIO_PIN_11
  *         @arg @ref LL_LPGPIO_PIN_12
  *         @arg @ref LL_LPGPIO_PIN_13
  *         @arg @ref LL_LPGPIO_PIN_14
  *         @arg @ref LL_LPGPIO_PIN_15
  *         @arg @ref LL_LPGPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void LL_LPGPIO_TogglePin(GPIO_TypeDef *LPGPIOx, uint32_t PinMask)
{
  WRITE_REG(LPGPIOx->ODR, READ_REG(LPGPIOx->ODR) ^ PinMask);
}


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup GPIO_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

ErrorStatus LL_LPGPIO_DeInit(GPIO_TypeDef *LPGPIOx);
ErrorStatus LL_LPGPIO_Init(GPIO_TypeDef *LPGPIOx, LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct);
void        LL_LPGPIO_StructInit(LL_LPGPIO_InitTypeDef *LPGPIO_InitStruct);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

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

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_LPGPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
