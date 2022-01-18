import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_if_simple_comma():
    result = subprocess.run(["./42sh", "-c", "if echo a; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if echo a; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_if_simple_without_comma():
    result = subprocess.run(["./42sh", "-c", "if echo a then echo b else echo c fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if echo a then echo b else echo c fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model


@pytest.mark.timeout(2)
def test_if_cond_test_comma():
    result = subprocess.run(["./42sh", "-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model
