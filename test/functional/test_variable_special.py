import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_special_code_value():
    os.popen("echo toto")
    result1 = subprocess.run(["./42sh", "-c", "echo $?"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("echo toto")
    model1 = subprocess.run(["bash", "--posix","-c", "$?"], stdout=subprocess.PIPE).stdout.decode('utf-8')

    os.popen("s")
    result2 = subprocess.run(["./42sh", "-c", "$?"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    os.popen("s")
    model2 = subprocess.run(["bash", "--posix","-c", "$?"], stderr=subprocess.PIPE).stderr.decode('utf-8')

    assert result1 == model1
    assert result2 == model2
