#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
project_path="$script_dir/.."
build_path="$project_path/build"

if [[ ! -d "$build_path" ]]; then
    CC=clang CXX=clang++ cmake -S "$project_path" -B "$build_path"
fi

make -C "$build_path" $@
