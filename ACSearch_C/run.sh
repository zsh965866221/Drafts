#!/bin/sh

python setup.py build
lib_path=$(ls build/|grep lib.|head -n 1)
export PYTHONPATH=build/${lib_path}:$PYTHONPATH
python test_py.py
python test_c.py
