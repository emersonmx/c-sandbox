#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXTERNALDIR="$SCRIPT_DIR/../external"

cd $EXTERNALDIR
rm -rf cglm
git clone https://github.com/recp/cglm.git
