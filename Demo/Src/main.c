#include "main.h"


// Define thread tasks
            osThreadId_t        GPIOTask;
const       osThreadAttr_t      GPIOTask_attributes = {
    .name = "GPIOTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 1024
};

            osThreadId_t        DebugTask;
const       osThreadAttr_t      DebugTask_attributes = {
    .name = "DebugTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 1024
};

            uint8_t             display_buffer[17] = { 0 };
            bool                use_i2c = false;
            bool                got_sensor = false;
__volatile  uint16_t            counter = 0;
            I2C_HandleTypeDef   i2c;


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    uint8_t buffer[35] = { 0 };
    mvGetDeviceId(buffer, 34);
    printf("Dev ID: ");
    printf((char *)buffer);
    printf("\n");
    printf("Build: %i\n", BUILD_NUM);

    // Reset of all peripherals, Initializes the Flash interface and the Systick.
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize peripherals
    GPIO_init();
    I2C_init();

    got_sensor = MCP9808_init();

    // Init scheduler
    osKernelInitialize();

    // Create the thread(s)
    // creation of defaultTask
    GPIOTask = osThreadNew(StartGPIOTask, NULL, &GPIOTask_attributes);
    DebugTask = osThreadNew(StartDebugTask, NULL, &DebugTask_attributes);

    // Start the scheduler
    osKernelStart();

    // We should never get here as control is now taken by the scheduler,
    // but just in case...
    while (1) {
        // NOP
    }
}


/**
  * @brief  Get the MV clock value
  * @retval The clock value
  */
uint32_t SECURE_SystemCoreClockUpdate() {
    uint32_t clock = 0;
    mvGetHClk(&clock);
    return clock;
}


/**
  * @brief  System clock configuration
  * @retval None
  */
void SystemClock_Config(void) {
    SystemCoreClockUpdate();
    HAL_InitTick(TICK_INT_PRIORITY);
}


/**
  * @brief  GPIO Initialization Function
  * @retval None
  */
void GPIO_init(void) {
    // Enable GPIO port clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pin output Level
    HAL_GPIO_WritePin(LED_GPIO_BANK, LED_GPIO_PIN, GPIO_PIN_RESET);

    // Configure GPIO pin : PA5 - Pin under test
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin   = LED_GPIO_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_GPIO_BANK, &GPIO_InitStruct);
}


/**
  * @brief  Function implementing the GPIO Task thread.
  * @param  argument: Not used
  * @retval None
  */
void StartGPIOTask(void *argument) {
    if (use_i2c) HT16K33_init();

    for(;;) {
        HAL_GPIO_TogglePin(LED_GPIO_BANK, LED_GPIO_PIN);
        if (use_i2c) HT16K33_show_value(counter++);
        if (counter > 9999) counter = 0;
        osDelay(DEFAULT_TASK_PAUSE);
    }
}


/**
  * @brief  Function implementing the Debug Task thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDebugTask(void *argument) {
    unsigned n = 0;

    for(;;) {
        printf("Debug ping %u seconds\n", n++);
        osDelay(DEBUG_TASK_PAUSE);

        if ((n % 30 == 0) && got_sensor) {
            double t = MCP9808_read_temp();
            printf("Temperature: %.02f\n", t);
        }
    }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    printf("FYI, an error occurred\n");
}