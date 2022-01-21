#!/bin/sh

python3 -m venv test-env
source test-env/bin/activate
pip install pytest

if [ $# -eq 1 ];
then
    for i in $*;
    do
        pytest "$i"
    done;
else
    pytest;
fi