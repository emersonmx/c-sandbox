#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="$SCRIPT_DIR/../build"

scons -Qc
bear scons -j20

pushd $BUILD_DIR
ln -sf ../compile_commands.json
popd
