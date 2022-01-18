import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_echo():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_bis():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    model = subprocess.run(["bash", "--posix","-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_middle():
    result = os.popen("./42sh -c \"echo Hello Friend\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_middle_single_quote():
    result = os.popen("./42sh -c \"echo 'Hello Friend'\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo 'Hello Friend'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_middle_double_quote():
    result = os.popen("./42sh -c \"echo \"Hello Friend\"\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo \"Hello Friend\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_long():
    result = os.popen("./42sh -c \"echo Hello My Friend It is a beautifull day to die\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend It is a beautifull day to die"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

# les points cassent tout
@pytest.mark.timeout(2)
def test_echo_long_point():
    result = os.popen("./42sh -c \"echo Hello My Friend. It is a beautifull day to die.\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

# apostrophe casse tout
@pytest.mark.timeout(2)
def test_echo_long_apostrophe():
    result = os.popen("./42sh -c \"echo Hello My Friend. It\'s a beautifull day to die.\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend. It\'s a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

# virgule casse tout
@pytest.mark.timeout(2)
def test_echo_long_comma():
    result = os.popen("./42sh -c \"echo Hello My Friend, It is a beautifull day to die.\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It is a beautifull day to die."], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

# all qui casse tout
@pytest.mark.timeout(2)
def test_echo_long_hard():
    result = os.popen("./42sh -c \"echo Hello My Friend, It's a beautifull day. To die !\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo Hello My Friend, It's a beautifull day. To die !"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_param_e_simple():
    result = os.popen("./42sh -c \"echo -e Hello\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo -e Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_param_e_long():
    result = os.popen("./42sh -c \"echo -e Hello Friend\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo -e Hello Friend"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_param_e_long_quotes():
    result = os.popen("./42sh -c \"echo -e \'Hello Friend\'\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo -e \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_param_e_long_double_quotes_backslash():
    result = os.popen("./42sh -c \"echo -e \"Hello\\nFriend\"\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo -e \"Hello\\nFriend\""], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model

@pytest.mark.timeout(2)
def test_echo_param_n():
    result = os.popen("./42sh -c \"echo -n \'Hello Friend\'\"").read()
    model = subprocess.run(["bash", "--posix","-c", "echo -n \'Hello Friend\'"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == model
