#!/bin/bash
set -e

cd $(dirname $0)

[ -d build ] && rm -rf build

./deploy.sh --genkeys --log
