cmake_minimum_required(VERSION 3.12)

add_executable(gpio_toggle_demo.elf
  Src/main.c
  Src/logging.c
  Src/http.c
  Src/stm32u5xx_hal_timebase_tim_template.c
)

target_include_directories(gpio_toggle_demo.elf PUBLIC
  Inc/
)

target_link_libraries(gpio_toggle_demo.elf LINK_PUBLIC ST_Code twilio-microvisor-hal-stm32u5 FreeRTOS)

# Optional informational and additional format generation
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
