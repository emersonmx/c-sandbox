#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EXTERNALDIR="$SCRIPT_DIR/../external"

function shallow_clone()
{
    git clone --depth=1 --shallow-submodules $1
}

cd $EXTERNALDIR
rm -rf cglm
shallow_clone https://github.com/recp/cglm.git
