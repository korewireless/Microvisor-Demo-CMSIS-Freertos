#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

twilio microvisor:deploy . --deviceseid ${MV_DEVICE_SID} --genkeys --log
