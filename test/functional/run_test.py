import subprocess
import pytest

def run_test_command(command):
    result = subprocess.run(["./42sh", "-c", command], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", command], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", command], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", command], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert (result_err == '') == (model_err == '')