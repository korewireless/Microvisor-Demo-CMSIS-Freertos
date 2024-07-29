/*
 *
 * Microvisor FreeRTOS Demo
 *
 * Copyright © 2024, KORE Wireless
 * Licence: MIT
 *
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
// Microvisor + HAL
#include "cmsis_os.h"
#include "mv_syscalls.h"
#include "stm32u5xx_hal.h"
// Application
#include "main.h"
#include "app_version.h"


/*
 * PRIVATE FUNCTION PROTOTYPES
 */
void        SystemClock_Config(void);
static void MX_GPIO_Init(void);
void        start_led_task(void *argument);
void        start_ping_task(void *argument);
static void post_log(bool is_err, const char* format_string, va_list args);
static void log_device_info(void);


/*
 * GLOBALS
 */
osThreadId_t led_task;
const osThreadAttr_t led_task_attributes = {
    .name = "LED Task",
    .priority = osPriorityNormal,
    .stack_size = configMINIMAL_STACK_SIZE
};

osThreadId_t ping_task;
const osThreadAttr_t ping_task_attributes = {
    .name = "PING Task",
    .priority = osPriorityNormal,
    .stack_size = 5120
};


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

    // Initialize application logging
    static uint8_t buffer[LOG_BUFFER_SIZE_B] __attribute__ ((aligned(512)));
    mvServerLoggingInit(buffer, sizeof(buffer));

    // Reset all peripherals, initialize the Flash interface and the Systick
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize all configured peripherals
    MX_GPIO_Init();

    // Log what's running here
    log_device_info();

    // Init the RTOS scheduler
    osKernelInitialize();

    // Establish the RTOS threads
    led_task  = osThreadNew(start_led_task,  NULL, &led_task_attributes);
    ping_task = osThreadNew(start_ping_task, NULL, &ping_task_attributes);

    // Start the RTOS scheduler
    osKernelStart();

    // We should never get here as control is now taken by the scheduler
    while (1) {
        __asm("nop");
    }
}


/**
 * @brief Get the MV clock value.
 *
 * @retval The clock value.
 */
uint32_t SECURE_SystemCoreClockUpdate() {

    uint32_t clock = 0;
    mvGetHClk(&clock);
    return clock;
}


/**
 * @brief System clock configuration.
 */
void SystemClock_Config(void) {

    SystemCoreClockUpdate();
    HAL_InitTick(TICK_INT_PRIORITY);
}


/**
 * @brief GPIO Initialization Function
 *
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE()

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA5 - Pin under test */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


/**
 * @brief Function implementing the LED flasher thread.
 *
 * @param argument: Not used.
 */
void start_led_task(void *argument) {

    /* Infinite loop */
    for(;;) {
        // Toggle GPIO PA5 -- the NDB's USER LED
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(LED_PAUSE_MS);
    }
}


/**
 * @brief  Function implementing the 'ping' logger thread.
 *
 * @param  argument: Not used.
 */
void start_ping_task(void *argument) {

    uint32_t count = 0;

    /* Infinite loop */
    for(;;) {
        server_log("Ping %u", count++);
        osDelay(PING_PAUSE_MS);
    }
}


/**
 * @brief This HAL-defined function is executed if an error occurs.
 *
 * @retval None
 */
void Error_Handler(void) {

    /* You can add your own implementation to
       report the HAL error return state */
    server_error("STM32 HAL error");
}


/**
 * @brief Issue a debug message.
 *
 * @param format_string Message string with optional formatting
 * @param ...           Optional injectable values
 */
void server_log(const char* format_string, ...) {

    va_list args;
    va_start(args, format_string);
    post_log(false, format_string, args);
    va_end(args);
}


/**
 * @brief Issue an error message.
 *
 * @param format_string Message string with optional formatting
 * @param ...           Optional injectable values
 */
void server_error(const char* format_string, ...) {

    va_list args;
    va_start(args, format_string);
    post_log(true, format_string, args);
    va_end(args);
}


/**
 * @brief Issue any log message.
 *
 * @param is_err        Is the message an error?
 * @param format_string Message string with optional formatting
 * @param args          va_list of args from previous call
 */
static void post_log(bool is_err, const char* format_string, va_list args) {

    char buffer[LOG_MESSAGE_MAX_LEN_B] = {0};
    uint32_t buffer_delta = 0;

    if (is_err) {
        // Write the message type to the message
        sprintf(buffer, "[ERROR] ");
        buffer_delta = 8;
    }

    // Write the formatted text to the message
    vsnprintf(&buffer[buffer_delta], sizeof(buffer) - buffer_delta - 1, format_string, args);

    // Output the message using the system call
    mvServerLog((const uint8_t*)buffer, (uint16_t)strlen(buffer));
}


/**
 * @brief Show basic device info.
 */
static void log_device_info(void) {

    uint8_t dev_id[35] = { 0 };
    mvGetDeviceId(dev_id, 34);
    server_log("Device: %s", dev_id);
    server_log("App: %s %s (BUILD %i)", APP_NAME, APP_VERSION, BUILD_NUM);
}


#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 *
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 */
void assert_failed(uint8_t *file, uint32_t line) {

    /* User can add their own implementation to
       report the file name and line number */
    server_error("Wrong parameter value: file %s on line %d\r\n", file, line) */
}
#endif  /* USE_FULL_ASSERT */
