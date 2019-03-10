#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LIBDIR="$SCRIPT_DIR/../libs"

cd $LIBDIR
rm -rf cglm
git clone https://github.com/recp/cglm.git
