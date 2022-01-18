import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_mkdir():
    os.popen("rm -r tess")
    os.popen("./42sh -c \"mkdir tess\"")
    result = os.popen("echo $?").read()
    assert result == '0\n'
    result = os.popen("ls tess").read()
    assert result == ''
    result = os.popen("rm -r tess").read()

    

@pytest.mark.timeout(2)
def test_rm_dir():
    os.popen("rm -r tess")
    os.popen("mkdir tess")
    result = os.popen("./42sh -c \"rm -r tess\"")
    result = os.popen("echo $?").read()
    assert result == '0\n'
    os.popen("rm -r tess")

@pytest.mark.timeout(2)
def test_touch():
    os.popen("rm -r tess")
    os.popen("mkdir tess")
    os.popen("./42sh -c \"touch tess/bite\"")
    result = os.popen("echo $?").read()
    assert result == '0\n'
    os.popen("./42sh -c \"cat tess/bite\"")
    result = os.popen("echo $?").read()
    assert result == '0\n'
    os.popen("rm -r tess")

@pytest.mark.timeout(3)
def test_ls():
    os.popen("mkdir tess")
    os.popen("touch tess/bite")
    result = os.popen("./42sh -c \"ls tess/\"").read()
    assert result == 'bite\n'
    os.popen("rm -r tess")
