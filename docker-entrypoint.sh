#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

if [[ ${MV_GA} == "true" ]]; then
  # Build only
  twilio microvisor:deploy . --devicesid ${MV_DEVICE_SID} -b
else 
  # Build and deploy -- requires env vars for device SID and Twilio creds to be set
  twilio microvisor:deploy . --devicesid ${MV_DEVICE_SID} --genkeys --log
fi
