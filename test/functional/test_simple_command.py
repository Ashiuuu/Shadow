import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_mkdir():
    os.popen("rm -r tess")
    os.popen("./42sh -c \"mkdir tess\"")
    
    result = subprocess.run(["./42sh", "-c", "mkdir tess"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result_ref = subprocess.run(["bash", "--posix", "-c", "mkdir tess"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result_err = subprocess.run(["./42sh", "-c", "mkdir tess"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    result_ref_err = subprocess.run(["bash", "--posix", "-c", "mkdir tess"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result1 = os.popen("echo $?").read()
    result2 = os.popen("ls tess").read()
    os.popen("rm -r tess").read()
    
    assert result == result_ref
    assert result_err == result_ref_err
    assert result1 == '0\n'
    assert result2 == ''

@pytest.mark.timeout(2)
def test_rm_dir():
    os.popen("rm -r tess")
    os.popen("mkdir tess")
    result = subprocess.run(["./42sh", "-c", "rm -r tess"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix", "-c", "rm -r tess"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "rm -r tess"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix", "-c", "rm -r tess"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    os.popen("rm -r tess")
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_touch():
    os.popen("rm -r tess")
    os.popen("mkdir tess")
    
    result = subprocess.run(["./42sh", "-c", "touch tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix", "-c", "touch tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("rm tess/bite")
    
    result_err = subprocess.run(["./42sh", "-c", "touch tess/bite"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix", "-c", "touch tess/bite"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result1 = subprocess.run(["./42sh", "-c", "cat tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix", "-c", "cat tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result1_err = subprocess.run(["./42sh", "-c", "cat tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1_err = subprocess.run(["bash", "--posix", "-c", "cat tess/bite"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("rm -r tess")

    assert result == model;
    assert result_err == model_err;
    assert result1 == model1;
    assert result1_err == model1_err;

@pytest.mark.timeout(5)
def test_ls():
    os.popen("mkdir tess")
    result = os.popen("echo $?").read()
    os.popen("touch tess/bite")
    result = os.popen("echo $?").read()
    result = os.popen("./42sh -c \"ls tess/\"").read()
    os.popen("rm -r tess")
    assert result == 'bite\n'
