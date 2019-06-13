#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
project_path="$script_dir/.."
externaldir="$script_dir/../external"
mkdir -p $externaldir

function shallow_clone()
{
    git clone --depth=1 --shallow-submodules $1
}

cd $externaldir

rm -rf Unity
shallow_clone https://github.com/ThrowTheSwitch/Unity.git
