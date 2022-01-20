import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_redir_right():
    result = subprocess.run(["./42sh", "-c", "echo a > t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo a > b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model
    result = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    assert result == model

@pytest.mark.timeout(2)
def test_redir_right_pipe():
    result1 = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result2 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result3 = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model3 = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result4 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model4 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    assert result1 == model1
    assert result2 == model2
    assert result3 == model3
    assert result4 == model4

@pytest.mark.timeout(2)
def test_redir_right_esperluette():
    result1 = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result2 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result3 = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model3 = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    result4 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model4 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    assert result1 == model1
    assert result2 == model2
    assert result3 == model3
    assert result4 == model4
    
