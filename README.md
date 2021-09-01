# FreeRTOS Microvisor Sample Project

This repo provides a basic demonstration of user application firmware based on the [FreeRTOS](https://freertos.org/) real-time OS and which will run on the “non-secure” side of Microvisor.

Most of the project files can be found in the [Demo/](Demo/) directory, including the `FreeRTOSConfig.h` and `stm32u5xx_hal_conf.h` configuration files.

The sample code toggles GPIO A5, which is the user LED on the Microvisor Nucleo board. It also emits a “ping” to the Microvisor logger once a second.

## Build with Docker

Build the image:

```shell
docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-gpio-sample-image .
```

Run the build:

```shell
docker run -it --rm -v $(pwd)/:/home/ --name microvisor-gpio-sample microvisor-gpio-sample-image
```

## Build in Ubuntu

The sample code has the following dependencies:

- `cmake`
- `gcc-arm-none-eabi` — tested with version 9-2019-q4

Prepare to build:

- Ensure all submodules are initialized:

        git submodule update --init --recursive

- Generate the Makefiles and project:

        cmake -S . -B build/

- Build the executable:

        cmake --build build --clean-first

The deliverable you can provision onto the Microvisor Nucleo board will be built into `build/Demo/gpio_toggle_demo.elf`.

## Copyright

The sample code is © 2021, Twilio, Inc.

FreeRTOS is © 2021, Amazon Web Services, Inc