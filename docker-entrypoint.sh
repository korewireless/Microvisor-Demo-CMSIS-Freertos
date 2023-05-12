#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

if [[ -n "${BUILD_ONLY}" ]]; then
  # Build only for GitHub tests
  twilio microvisor:deploy . -b
else
  # Build and deploy -- requires env vars for device SID and Twilio creds to be set
  twilio microvisor:deploy . --devicesid ${MV_DEVICE_SID} --genkeys --log
fi
