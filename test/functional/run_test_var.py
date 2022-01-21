import subprocess
import pytest

@pytest.mark.timeout(2)
def run_test_var(scrypt):
    result1 = subprocess.run(["./42sh", "-c", scrypt], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", scrypt], stdout=subprocess.PIPE).stdout.decode('utf-8')

    assert result1 == model1