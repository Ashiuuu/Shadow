import subprocess
import os
import pytest

import run_test

@pytest.mark.timeout(5)
def test_script_echo():
    run_test.run_test_command("test/functional/test.sh")

@pytest.mark.timeout(5)
def test_script_if_success():
    run_test.run_test_command("test/functional/test_if.sh")

@pytest.mark.timeout(5)
def test_script_if_fail():
    run_test.run_test_command("test/functional/test_if_fail.sh")
