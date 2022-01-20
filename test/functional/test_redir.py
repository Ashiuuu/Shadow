import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_redir_right():
    result1 = subprocess.run(["./42sh", "-c", "echo a > t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo a > b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result1_err = subprocess.run(["./42sh", "-c", "echo a > t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model1_err = subprocess.run(["bash", "--posix","-c", "echo a > b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result2 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result2_err = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model2_err = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    
    assert result1 == model1
    assert result1_err == model1_err
    assert result2 == model2
    assert result2_err == model2_err

@pytest.mark.timeout(2)
def test_redir_right_pipe():
    result1 = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result1_err = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model1_err = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result2 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result3 = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model3 = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result3_err = subprocess.run(["./42sh", "-c", "echo a >| t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model3_err = subprocess.run(["bash", "--posix","-c", "echo a >| b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result4 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model4 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    
    assert result1 == model1
    assert result1_err == model1_err
    assert result2 == model2
    assert result3 == model3
    assert result3_err == model3_err
    assert result4 == model4

@pytest.mark.timeout(2)
def test_redir_right_esperluette():
    result1 = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model1 = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result1_err = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model1_err = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result2 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model2 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result3 = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model3 = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result3_err = subprocess.run(["./42sh", "-c", "echo a >& t.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model3_err = subprocess.run(["bash", "--posix","-c", "echo a >& b.txt"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    result4 = subprocess.run(["bash", "--posix","-c", "cat t.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model4 = subprocess.run(["bash", "--posix","-c", "cat b.txt"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    os.popen("rm b.txt")
    os.popen("rm t.txt")
    
    assert result1 == model1
    assert result1_err == model1_err
    assert result2 == model2
    assert result3 == model3
    assert result3_err == model3_err
    assert result4 == model4
    
