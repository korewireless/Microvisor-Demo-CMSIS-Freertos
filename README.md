# FreeRTOS Microvisor Sample Project

This is a simple demonstration of user firmware based on FreeRTOS which will run on the "non-secure" side of Microvisor.

The modified files mostly live in the [Demo/](Demo/) directory, including the `FreeRTOSConfig.h` and `stm32u5xx_hal_conf.h` configurations.

The sample toggles a non-secure GPIO on port F, pin 0 once a second.  It also emits a "ping" to the Microvisor logger once a second.

## Building with Docker

Building the image:

        docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-gpio-sample-image .

Running the build:

        docker run -it --rm -v $(pwd)/:/home/ --name microvisor-gpio-sample microvisor-gpio-sample-image

## Building in Ubuntu

Dependencies:

- cmake
- gcc-arm-none-eabi (tested with 9-2019-q4)
- `mv_api.h` and `mv_implib.o` somewhere on your system

Getting ready to build:

- Generate the Makefiles and project.  Instead of providing a path to
`MV_IMPLIB_DIR`, you can also copy the `mv_api.h` and `mv_implib.o`
files into the uapi/ directory in this project and omit that parameter:

        cmake -D MV_IMPLIB_DIR="~/ei/uapi/" -S . -B build/

- Build the executable:

        cmake --build build --clean-first

The deliverable you can provision onto Microvisor will be built into `build/gpio_toggle_demo.elf`.
