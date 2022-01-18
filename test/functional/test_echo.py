import subprocess
import os
import pytest

@pytest.mark.timeout(2)
def test_echo():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result == 'Hello\n'

@pytest.mark.timeout(2)
def test_echo_middle():
    result = os.popen("./42sh -c \"echo Hello Friend\"").read()
    assert result == 'Hello\nFriend\n'

@pytest.mark.timeout(2)
def test_echo_middle_single_quote():
    result = os.popen("./42sh -c \"echo 'Hello Friend'\"").read()
    assert result == 'Hello Friend\n'

@pytest.mark.timeout(2)
def test_echo_middle_double_quote():
    result = os.popen("./42sh -c \"echo \"Hello Friend\"\"").read()
    assert result == 'Hello Friend\n'

@pytest.mark.timeout(2)
def test_echo_long():
    result = os.popen("./42sh -c \"echo Hello My Friend It is a beautifull day to die\"").read()
    assert result == 'Hello\nMy\nFriend\nIt\nis\na\nbeautifull\nday\nto\ndie\n'

# les points cassent tout
@pytest.mark.timeout(2)
def test_echo_long_point():
    result = os.popen("./42sh -c \"echo Hello My Friend. It is a beautifull day to die.\"").read()
    assert result == 'Hello\nMy\nFriend.\nIt\'is\na\nbeautifull\nday\nto\ndie.\n'

# apostrophe casse tout
@pytest.mark.timeout(2)
def test_echo_long_apostrophe():
    result = os.popen("./42sh -c \"echo Hello My Friend. It\'s a beautifull day to die.\"").read()
    assert result == 'Hello\nMy\nFriend.\nIt\'s\na\nbeautifull\nday\nto\ndie.\n'

# virgule casse tout
@pytest.mark.timeout(2)
def test_echo_long_comma():
    result = os.popen("./42sh -c \"echo Hello My Friend, It is a beautifull day to die.\"").read()
    assert result == 'Hello\nMy\nFriend,\nIt\nis\na\nbeautifull\nday\nto\ndie.\n'

# all qui casse tout
@pytest.mark.timeout(2)
def test_echo_long_hard():
    result = os.popen("./42sh -c \"echo Hello My Friend, It's a beautifull day. To die !\"").read()
    assert result == 'Hello\nMy\nFriend,\nIt\'s\na\nbeautifull\nday.\nto\ndie\n!\n'

@pytest.mark.timeout(2)
def test_echo_parma_e_simple():
    result = os.popen("./42sh -c \"echo -e Hello\"").read()
    assert result == 'Hello\n'

@pytest.mark.timeout(2)
def test_echo_parma_e_long():
    result = os.popen("./42sh -c \"echo -e Hello Friend\"").read()
    assert result == 'Hello Friend\n'