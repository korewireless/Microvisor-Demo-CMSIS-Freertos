cmake_minimum_required(VERSION 3.12)

set(MV_IMPLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/uapi" CACHE FILEPATH "")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

project(gpio_toggle_demo.elf C ASM)

add_executable(gpio_toggle_demo.elf
  ${MV_IMPLIB_DIR}/mv_implib.o
  Demo/Src/main.c
  Demo/Src/stm32u5xx_hal_timebase_tim_template.c
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/STM32U585xx_FLASH_mv.ld")

target_link_libraries(gpio_toggle_demo.elf ST_Code FreeRTOS)

target_include_directories(gpio_toggle_demo.elf PUBLIC
  Demo/Inc/
  ${MV_IMPLIB_DIR}/
)

add_library(ST_Code STATIC
  ST_Code/Core/Src/syscalls.c ST_Code/Core/Src/sysmem.c
  ST_Code/Core/Src/stm32u5xx_hal_msp.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash_ex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gtzc.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c_ex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_icache.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim.c
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim_ex.c
  ST_Code/Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.c
  ST_Code/CMSIS_RTOS_V2/cmsis_os2.c
  ST_Code/Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/gcc/startup_stm32u585xx.s
)

target_include_directories(ST_Code PUBLIC
  Config/
  FreeRTOS-Kernel/include
  FreeRTOS-Kernel/portable/GCC/ARM_CM33_NTZ/non_secure
  ST_Code/CMSIS_RTOS_V2
  ST_Code/Core/Inc
  ST_Code/Drivers/CMSIS/Device/ST/STM32U5xx/Include
  ST_Code/Drivers/CMSIS/Include
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Inc
  ST_Code/Drivers/STM32U5xx_HAL_Driver/Inc/Legacy
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

add_custom_command(OUTPUT EXTRAS
  DEPENDS gpio_toggle_demo.elf
  COMMAND ${CMAKE_SIZE} --format=berkeley "gpio_toggle_demo.elf"
  COMMAND ${CMAKE_OBJDUMP} -h -S "gpio_toggle_demo.elf" > "gpio_toggle_demo.list"
  COMMAND ${CMAKE_OBJCOPY} -O binary "gpio_toggle_demo.elf" "gpio_toggle_demo.bin"
)

add_custom_target(extras ALL
  ${CMAKE_COMMAND} -E echo "Outputting additional artifacts"
  DEPENDS EXTRAS
)
