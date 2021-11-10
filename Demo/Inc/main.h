#ifndef _MAIN_H_
#define _MAIN_H_


#ifdef __cplusplus
extern "C" {
#endif


/*
 * INCLUDES
 */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include "stm32u5xx_hal.h"
#include "cmsis_os.h"
#include "mv_syscalls.h"

#include "logging.h"
#include "ht16k33.h"
#include "i2c.h"
#include "mcp9808.h"


/*
 * CONSTANTS
 */
#define     LED_GPIO_BANK           GPIOA
#define     LED_GPIO_PIN            GPIO_PIN_5
#define     LED_FLASH_PERIOD        1000

#define     DEBUG_TASK_PAUSE        1000
#define     DEFAULT_TASK_PAUSE      500


/*
 * PROTOTYPES
 */
void        Error_Handler(void);
void        SystemClock_Config(void);
void        StartGPIOTask(void *argument);
void        StartDebugTask(void *argument);

void        GPIO_init(void);


#ifdef __cplusplus
}
#endif


#endif      // _MAIN_H_