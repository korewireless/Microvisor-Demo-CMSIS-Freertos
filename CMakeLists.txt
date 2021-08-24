cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

project(gpio_toggle_demo.elf C ASM)

add_library(twilio-microvisor-hal STATIC
  ST_Code/Core/Src/syscalls.c ST_Code/Core/Src/sysmem.c
  ST_Code/Core/Src/stm32u5xx_hal_msp.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash_ex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gtzc.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c_ex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_icache.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim.c
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim_ex.c
  twilio-microvisor-hal/Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.c
  ST_Code/CMSIS_RTOS_V2/cmsis_os2.c
  twilio-microvisor-hal/Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/gcc/startup_stm32u585xx.s
)

target_include_directories(twilio-microvisor-hal PUBLIC
  Config/
  FreeRTOS-Kernel/include
  FreeRTOS-Kernel/portable/GCC/ARM_CM33_NTZ/non_secure
  ST_Code/CMSIS_RTOS_V2
  ST_Code/Core/Inc
  twilio-microvisor-hal/
  twilio-microvisor-hal/Drivers/CMSIS/Device/ST/STM32U5xx/Include
  twilio-microvisor-hal/Drivers/CMSIS/Include
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Inc
  twilio-microvisor-hal/Drivers/STM32U5xx_HAL_Driver/Inc/Legacy
  twilio-microvisor-sdk/
)

add_library(FreeRTOS STATIC
  FreeRTOS-Kernel/croutine.c
  FreeRTOS-Kernel/event_groups.c
  FreeRTOS-Kernel/list.c
  FreeRTOS-Kernel/queue.c
  FreeRTOS-Kernel/stream_buffer.c
  FreeRTOS-Kernel/tasks.c
  FreeRTOS-Kernel/timers.c
  FreeRTOS-Kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.c
  FreeRTOS-Kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c
  FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories(FreeRTOS PUBLIC
  Config/
  FreeRTOS-Kernel/include
  FreeRTOS-Kernel/portable/GCC/ARM_CM33_NTZ/non_secure
)

add_subdirectory(twilio-microvisor-sdk)
add_subdirectory(Demo)
