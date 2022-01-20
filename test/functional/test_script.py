import subprocess
import os
import pytest

@pytest.mark.timeout(5)
def test_script_echo():
    result = subprocess.run(["./42sh", "test/functional/test.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","test/functional/test.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(5)
def test_script_if_success():
    result = subprocess.run(["./42sh", "test/functional/test_if.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","test/functional/test_if.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(5)
def test_script_if_fail():
    result = subprocess.run(["./42sh", "test/functional/test_if_fail.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","test/functional/test_if_fail.sh"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model