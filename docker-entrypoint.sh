#!/bin/bash
set -e

if [ -d build ]; then
  rm -rf build
fi

mkdir build
cd build
cmake ..
make -j6
python3 ../twilio-microvisor-tools/bundler-py/bundler.py Demo/gpio_toggle_demo.elf Demo/gpio_toggle_demo.zip
