import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_if_simple_comma():
    result = subprocess.run(["./42sh", "-c", "if echo a; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if echo a; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')

    result_err = subprocess.run(["./42sh", "-c", "if echo a; then echo b; else echo c; fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "if echo a; then echo b; else echo c; fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')

    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_if_simple_without_comma():
    result = subprocess.run(["./42sh", "-c", "if echo a then echo b else echo c fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if echo a then echo b else echo c fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')

    result_err = subprocess.run(["./42sh", "-c", "if echo a then echo b else echo c fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "if echo a then echo b else echo c fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')

    assert result == model
    assert (result_err == '') == (model_err == '')
    #assert result_err == model_err


@pytest.mark.timeout(2)
def test_if_cond_test_comma():
    result = subprocess.run(["./42sh", "-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "if [ 1 -eq 1 ]; then echo b; else echo c; fi"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_if_wrong_syntax():
    result = subprocess.run(["./42sh", "-c", "if echo a; then echo couille;"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix", "if echo a; then echo couille;"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "if echo a; then echo couille;"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix", "if echo a; then echo couille;"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert (result_err == '') == (model_err == '')
    #assert result_err == model_err
