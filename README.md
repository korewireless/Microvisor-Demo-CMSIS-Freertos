# FreeRTOS Microvisor Sample Project

This repo provides a basic demonstration of user application firmware based on the [FreeRTOS](https://freertos.org/) real-time operating system and which will run on the “non-secure” side of Microvisor.

The [ARM CMSIS-RTOS API](https://github.com/ARM-software/CMSIS_5) is used an an intermediary between the application and FreeRTOS to make it easier to swap out the RTOS layer for another.

Most of the project files can be found in the [Demo/](Demo/) directory. The [ST_Code/](ST_Code/) directory contains required components that are not part of Twilio Microvisor STM32U5 HAL, which this sample accesses as a submodule. FreeRTOS is also incorporated as a submodule.

The `FreeRTOSConfig.h` and `stm32u5xx_hal_conf.h` configuration files are located in the [Config/](Config/) directory.

The sample code toggles GPIO PA5, which is the user LED on the [Microvisor Nucleo Development Board](https://www.twilio.com/docs/iot/microvisor/get-started-with-microvisor). It also emits a “ping” to the Microvisor logger once a second.

## Platform Support

We currently support the following build platforms:

* Linux — native development under [Ubuntu 20.0.4](#build-in-ubuntu).
* Windows — development in [Ubuntu 20.0.4 via Windows Subsystem for Linux 2](#build-under-windows).
* Mac — development via [Docker container](#build-with-docker).

## Build under Windows

The recommended solution for working with Microvisor on Windows is via [Windows Subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install).

You will need Administrator privileges to install WSL.

### Install WSL

1. Open an Administrator-level Powershell instance.
1. Run `wsl --install -d ubuntu`.
1. Open the Ubuntu instance shell from your Start menu and [follow the Ubuntu instructions below](#build-in-ubuntu).

## Build with Docker

If you are running on an architecture other than x86/amd64 (such as a Mac with Apple silicon), you will need to override the platform when running docker. This is needed for the `twilio-cli` `apt` package which is x86 only at this time:

```shell
export DOCKER_DEFAULT_PLATFORM=linux/amd64
```

Build the image:

```shell
docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-freertos-image .
```

Run the build:

```shell
docker run -it --rm -v $(pwd)/:/home/mvisor/project/ \
  --env-file env.list \
  --name microvisor-freertos microvisor-freertos-image
```

Under Docker, the demo is compiled, uploaded and deployed to your development board. It also initiates logging — hit <b>ctrl</b>-<b>c</b> to break out to the command prompt.

## Build in Ubuntu

### Install Libraries and Tools

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

The process outlined below requires Plugin 0.3.10 or above.

### Set Environment Variables

Running the Twilio CLI and the Microvisor Plugin for uploading the built code to the Twilio cloud and subsequent deployment to your Microvisor Nucleo Board uses the following Twilio credentials stored as environment variables. They should be added to your shell profile:

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

It is also accessible via the QR code on the back of your development board. Scan the code with your mobile phone and a suitable app, and the board’s SID is the third `/`-separated field.

### Build and Deploy the Demo

```bash
cd twilio-microvisor-freertos
twilio microvisor:deploy . --devicesid ${MV_DEVICE_SID} --log
```

This will compile, bundle and upload the code, and stage it for deployment to your device. If you encounter errors, please check your stored Twilio credentials.

The `--log` flag initiates log-streaming.

#### View Log Output

You can start log streaming without first building and/or deploying new code with this command:

```bash
twilio microvisor:deploy . --devicesid ${MV_DEVICE_SID} --logonly
```

You can build but not deploy with this command:

```bash
twilio microvisor:deploy . --build
```

You can deploy the most recent build with this command:

```bash
twilio microvisor:deploy . --device-sid ${MV_DEVICE_SID} --deploy
```

You can clean the most build directory before compiling with this command:

```bash
twilio microvisor:deploy . --device-sid ${MV_DEVICE_SID} --clean
```

For more information, run:

```bash
twilio microvisor:deploy --help
```

## Repo Updates

Update the repo’s submodules to their remotes’ latest commits with:

```shell
cd /path/to/twilio-microvisor-freertos
git submodule update --init --remote --recursive
```

## Support/Feedback

Please contact [Twilio Support](https://support.twilio.com/).

## More Samples

Please see [Microvisor Sample Code](https://www.twilio.com/docs/iot/microvisor/sample-code).

## Copyright

The sample code is © 2023, Twilio, Inc.

FreeRTOS is © 2021, Amazon Web Services, Inc
