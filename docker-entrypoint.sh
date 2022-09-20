#!/bin/bash
set -e

cd $(dirname $0)

if [ -d build ]; then
  rm -rf build
fi

mkdir -p build
cd build
cmake ..
make -j6

ARGS=""
if [ -f ../debug-public-key.pem ]; then
  ARGS="${ARGS} --debug-auth-pubkey=../debug-public-key.pem"
fi
twilio microvisor:apps:bundle -l debug ${ARGS} \
  Demo/gpio_toggle_demo.bin \
  Demo/gpio_toggle_demo.zip
