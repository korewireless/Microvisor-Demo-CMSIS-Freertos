# FreeRTOS Microvisor Sample Project

This is a simple demonstration of user firmware based on FreeRTOS which will run on the "non-secure" side of Microvisor.

The modified files mostly live in the [Demo/](Demo/) directory, including the `FreeRTOSConfig.h` and `stm32u5xx_hal_conf.h` configurations.

The sample toggles GPIO A5, which is the user led on the Microvisor Nucleo board.  It also emits a "ping" to the Microvisor logger once a second.

## Building with Docker

Building the image:

        docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-gpio-sample-image .

Running the build:

        docker run -it --rm -v $(pwd)/:/home/ --name microvisor-gpio-sample microvisor-gpio-sample-image

## Building in Ubuntu

Dependencies:

- cmake
- gcc-arm-none-eabi (tested with 9-2019-q4)

Getting ready to build:

- Ensure all submodules are initialized:

        git submodule update --init --recursive

- Generate the Makefiles and project:

        cmake -S . -B build/

- Build the executable:

        cmake --build build --clean-first

The deliverable you can provision onto Microvisor will be built into `build/Demo/gpio_toggle_demo.elf`.
