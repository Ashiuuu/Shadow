import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_echo():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_bis():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_middle():
    result = subprocess.run(["./42sh","-c", "echo Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo Hello Friend"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello Friend"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_middle_single_quote():
    result = subprocess.run(["./42sh","-c", "echo 'Hello Friend'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo 'Hello Friend'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo 'Hello Friend'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo 'Hello Friend'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_middle_double_quote():
    result = subprocess.run(["./42sh", "-c", "echo \"Hello Friend\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo \"Hello Friend\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo \"Hello Friend\""], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo \"Hello Friend\""], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_long():
    result = subprocess.run(["./42sh","-c", "echo Hello My Friend It is a beautifull day to die"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend It is a beautifull day to die"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo Hello My Friend It is a beautifull day to die"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend It is a beautifull day to die"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

# les points cassent tout
@pytest.mark.timeout(2)
def test_echo_long_point():
    result = subprocess.run(["./42sh","-c", "echo Hello My Friend. It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo Hello My Friend. It is a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It is a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

# apostrophe casse tout
@pytest.mark.timeout(2)
def test_echo_long_apostrophe():
    result = subprocess.run(["./42sh","-c", "echo Hello My Friend. It\'s a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It\'s a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo Hello My Friend. It\'s a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It\'s a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert (result_err == '') == (model_err == '')
    #assert result_err == model_err

# virgule casse tout
@pytest.mark.timeout(2)
def test_echo_long_comma():
    result = subprocess.run(["./42sh","-c", "echo Hello My Friend, It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo Hello My Friend, It is a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It is a beautifull day to die."], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

# all qui casse tout
@pytest.mark.timeout(2)
def test_echo_long_hard():
    result = subprocess.run(["./42sh","-c", "echo Hello My Friend, It's a beautifull day. To die !"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It's a beautifull day. To die !"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo Hello My Friend, It's a beautifull day. To die !"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It's a beautifull day. To die !"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert (result_err == '') == (model_err == '')
    #assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_param_e_simple():
    result = subprocess.run(["./42sh","-c", "echo -e Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo -e Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo -e Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo -e Hello"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_param_e_long():
    result = subprocess.run(["./42sh", "-c", "echo -e Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo -e Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo -e Hello Friend"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo -e Hello Friend"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_param_e_long_quotes():
    result = subprocess.run(["./42sh","-c", "echo -e \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo -e \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo -e \'Hello Friend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo -e \'Hello Friend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_param_e_long_double_quotes_backslash():
    result = subprocess.run(["./42sh", "-c", "echo -e \'Hello\\nFriend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix", "-c", "echo -e \'Hello\\nFriend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh", "-c", "echo -e \'Hello\\nFriend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo -e \'Hello\\nFriend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err

@pytest.mark.timeout(2)
def test_echo_param_n():
    result = subprocess.run(["./42sh","-c", "echo -n \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo -n \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    
    result_err = subprocess.run(["./42sh","-c", "echo -n \'Hello Friend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    model_err = subprocess.run(["bash", "--posix","-c", "echo -n \'Hello Friend\'"], stderr=subprocess.PIPE).stderr.decode('utf-8')
    
    assert result == model
    assert result_err == model_err
