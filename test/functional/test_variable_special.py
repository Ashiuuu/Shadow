import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_special_code_value():
    result1 = subprocess.run(["./42sh", "-c", "echo toto; echo \"$?\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo toto; echo \"$?\""], stdout=subprocess.PIPE).stdout.decode('utf-8')

    result2 = subprocess.run(["./42sh", "-c", "s; echo \"$?\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "s; echo \"$?\""], stdout=subprocess.PIPE).stdout.decode('utf-8')

    assert result1 == model1
    assert result2 == model2
