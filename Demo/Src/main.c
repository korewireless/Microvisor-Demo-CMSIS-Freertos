/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "main.h"
#include "cmsis_os.h"
#include "mv_syscalls.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Definitions for defaultTask */
osThreadId_t GPIOTask;
const osThreadAttr_t GPIOTask_attributes = {
    .name = "GPIOTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = configMINIMAL_STACK_SIZE
};

osThreadId_t DebugTask;
const osThreadAttr_t DebugTask_attributes = {
    .name = "DebugTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 5120
};

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void        SystemClock_Config(void);
static void MX_GPIO_Init(void);
void        StartGPIOTask(void *argument);
void        StartDebugTask(void *argument);
static void post_log(bool is_err, char* format_string, va_list args);
static void log_device_info(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    
    /* USER CODE BEGIN 1 */
    static uint8_t buffer[LOG_BUFFER_SIZE_B] __attribute__ ((aligned(512)));
    mvServerLoggingInit(buffer, sizeof(buffer));
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    
    /* USER CODE BEGIN 2 */
    log_device_info();
    /* USER CODE END 2 */

    /* Init scheduler */
    osKernelInitialize();

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    GPIOTask  = osThreadNew(StartGPIOTask,  NULL, &GPIOTask_attributes);
    DebugTask = osThreadNew(StartDebugTask, NULL, &DebugTask_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1) {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
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
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA5 - Pin under test */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartGPIOTask */
/**
 * @brief  Function implementing the defaultTask thread.
 *
 * @param  argument: Not used
 *
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartGPIOTask(void *argument) {
    
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for(;;) {
        // Toggle GPIO PA5 -- the NDB's USER LED
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(DEBUG_LED_PAUSE_MS);
    }
    /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartDebugTask */
/**
 * @brief  Function implementing the defaultTask thread.
 *
 * @param  argument: Not used
 *
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDebugTask(void *argument) {
    
    /* USER CODE BEGIN 5 */
    //server_log("%s %s", APP_NAME, APP_VERSION);
    uint32_t count = 0;

    /* Infinite loop */
    for(;;) {
        server_log("Ping %u", count++);
        osDelay(DEBUG_PING_PAUSE_MS);
    }
    /* USER CODE END 5 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 *
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif  /* USE_FULL_ASSERT */

/**
 * @brief Issue a debug message.
 *
 * @param format_string Message string with optional formatting
 * @param ...           Optional injectable values
 */
void server_log(char* format_string, ...) {
    
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
void server_error(char* format_string, ...) {
    
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
static void post_log(bool is_err, char* format_string, va_list args) {
    
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
    server_log("   App: %s %s", APP_NAME, APP_VERSION);
    server_log(" Build: %i", BUILD_NUM);
}
