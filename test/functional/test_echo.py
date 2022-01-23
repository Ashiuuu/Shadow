import pytest

import run_test

@pytest.mark.timeout(2)
def test_echo():
    run_test.run_test_command("echo Hello")

@pytest.mark.timeout(2)
def test_echo_middle():
    run_test.run_test_command("echo Hello Friend")

@pytest.mark.timeout(2)
def test_echo_middle_single_quote():
    run_test.run_test_command("echo 'Hello Friend'")

@pytest.mark.timeout(2)
def test_echo_middle_double_quote():
    run_test.run_test_command("echo \"Hello Friend\"")

@pytest.mark.timeout(2)
def test_echo_long():
    run_test.run_test_command("echo Hello My Friend It is a beautifull day to die")

# les points cassent tout
@pytest.mark.timeout(2)
def test_echo_long_point():
    run_test.run_test_command("echo Hello My Friend. It is a beautifull day to die.")

# apostrophe casse tout
@pytest.mark.timeout(2)
def test_echo_long_apostrophe():
    run_test.run_test_command("echo Hello My Friend. It\'s a beautifull day to die.")

# virgule casse tout
@pytest.mark.timeout(2)
def test_echo_long_comma():
    run_test.run_test_command("echo Hello My Friend, It is a beautifull day to die.")

# all qui casse tout
@pytest.mark.timeout(2)
def test_echo_long_hard():
    run_test.run_test_command("echo Hello My Friend, It's a beautifull day. To die !")

@pytest.mark.timeout(2)
def test_echo_param_e_simple():
    run_test.run_test_command("echo -e Hello")

@pytest.mark.timeout(2)
def test_echo_param_e_long():
    run_test.run_test_command("echo -e Hello Friend")

@pytest.mark.timeout(2)
def test_echo_param_e_long_quotes():
    run_test.run_test_command("echo -e \'Hello Friend\'")

@pytest.mark.timeout(2)
def test_echo_param_e_long_double_quotes_backslash():
    run_test.run_test_command("echo -e \'Hello\\nFriend\'")

@pytest.mark.timeout(2)
def test_echo_param_n():
    run_test.run_test_command("echo -n \'Hello Friend\'")

@pytest.mark.timeout(2)
def test_echo_param_e_hard():
    run_test.run_test_command("echo -e \'\t \n Hello Friend\'")

@pytest.mark.timeout(2)
def test_echo_param_e_hard():
    run_test.run_test_command("echo -e \t \n Hello Friend")
