# FreeRTOS Microvisor Sample Project

This repo provides a basic demonstration of user application firmware based on the [FreeRTOS](https://freertos.org/) real-time operating system and which will run on the “non-secure” side of Microvisor.

The [ARM CMSIS-RTOS API](https://github.com/ARM-software/CMSIS_5) is used an an intermediary between the application and FreeRTOS to make it easier to swap out the RTOS layer for another.

Most of the project files can be found in the [Demo/](Demo/) directory. The [ST_Code/](ST_Code/) directory contains required components that are not part of Twilio Microvisor STM32U5 HAL, which this sample accesses as a submodule. FreeRTOS is also incorporated as a submodule.

The `FreeRTOSConfig.h` and `stm32u5xx_hal_conf.h` configuration files are located in the [Config/](Config/) directory.

The sample code toggles GPIO PA5, which is the user LED on the [Microvisor Nucleo Development Board](https://www.twilio.com/docs/iot/microvisor/get-started-with-microvisor). It also emits a “ping” to the Microvisor logger once a second.

## Build with Docker

If you are running on an architecture other than x86/amd64 (such as a Mac with Apple silicon), you will need to override the platform when running docker.  This is needed for the twilio-cli apt package which is x86 only at this time:

```shell
export DOCKER_DEFAULT_PLATFORM=linux/amd64
```

Build the image:

```shell
docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-gpio-sample-image .
```

Run the build:

```shell
docker run -it --rm -v $(pwd)/:/home/mvisor/project/ --name microvisor-gpio-sample microvisor-gpio-sample-image
```

The bundle for submission to Twilio for deployment will be `build/Demo/gpio_toggle_demo.zip`.

Debugging:

```shell
docker run -it --rm -v $(pwd)/:/home/mvisor/project/ --name microvisor-gpio-sample-debug --entrypoint /bin/bash microvisor-gpio-sample-image
```

**Note** You will need to have exported certain environment variables, as [detailed below](#environment-variables).

Under Docker, the demo is compiled, uploaded and deployed to your development board. It also initiates logging — hit <b>ctrl</b>-<b>c</b> to break out to the command prompt.

## Build in Ubuntu

### Libraries and Tools

Under Ubuntu, run the following:

```bash
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi \
  git curl build-essential cmake libsecret-1-dev jq openssl
```

### Twilio CLI

Install the Twilio CLI. This is required to view streamed logs and for remote debugging. You need version 4.0.1 or above.

**Note** If you have already installed the Twilio CLI using *npm*, we recommend removing it and then reinstalling as outlined below. Remove the old version with `npm remove -g twilio-cli`.

```bash
wget -qO- https://twilio-cli-prod.s3.amazonaws.com/twilio_pub.asc | sudo apt-key add -
sudo touch /etc/apt/sources.list.d/twilio.list
echo 'deb https://twilio-cli-prod.s3.amazonaws.com/apt/ /' | sudo tee /etc/apt/sources.list.d/twilio.list
sudo apt update
sudo apt install -y twilio
```

Close your terminal window or tab, and open a new one. Now run:

```bash
twilio plugins:install @twilio/plugin-microvisor
```

### Set Environment Variables

Running the Twilio CLI and the project's [deploy script](./deploy.sh) — for uploading the built code to the Twilio cloud and subsequent deployment to your Microvisor Nucleo Board — uses the following Twilio credentials stored as environment variables. They should be added to your shell profile:

```bash
export TWILIO_ACCOUNT_SID=ACxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
export TWILIO_AUTH_TOKEN=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
export MV_DEVICE_SID=UVxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```

You can get the first two from your Twilio Console [account dashboard](https://console.twilio.com/).

Enter the following command to get your target device’s SID and, if set, its unique name:

```bash
twilio api:microvisor:v1:devices:list
```

It is also accessible via the QR code on the back of your development board.

### Build and Deploy the Demo

Run:

```bash
./deploy.sh --log
```

This will compile, bundle and upload the code, and stage it for deployment to your device. If you encounter errors, please check your stored Twilio credentials.

The `--log` flag initiates log-streaming.

#### View Log Output

You can start log streaming separately with this command:

```bash
./deploy.sh --logonly
```

You can build but not deploy with this command:

```bash
./deploy.sh -b
```

You can deploy the most recent build with this command:

```bash
./deploy.sh -d
```

For more information, run

```bash
./deploy.sh --help
```

## Repo Updates

Update the repo’s submodules to their remotes’ latest commits with:

```shell
cd /path/to/twilio-microvisor-freertos
git submodule update --init --remote --recursive
```

## Support/Feedback

Please contact [Twilio Support](https://support.twilio.com/).

## Copyright

The sample code is © 2023, Twilio, Inc.

FreeRTOS is © 2021, Amazon Web Services, Inc
