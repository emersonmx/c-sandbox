#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
EDITOR_CONFIG="$HOME/.config/nvim/init.vim"

function reset_file()
{
    rm -f "$1"
    touch "$filename"
}

function make_snippet()
{
    filename="$1"
    snippet="$2"

    echo "Creating $filename"
    reset_file $filename
    $EDITOR -u $EDITOR_CONFIG -es $filename <<-SCRIPT
execute "normal! \<esc>a$snippet\<c-r>=UltiSnips#ExpandSnippet()\<cr>\<esc>:w\<cr>"
SCRIPT
    echo "Done."
}

make_snippet .vmx sctempl

cp -vf $script_dir/stubs/gitignore .gitignore
cp -vf $script_dir/stubs/projections.json .projections.json
cp -vf $script_dir/stubs/shenv .shenv
cp -vf $script_dir/stubs/CMakeLists.txt .
