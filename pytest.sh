#!/bin/sh

python3 -m venv test-env
source test-env/bin/activate
pip install pytest
pytest
