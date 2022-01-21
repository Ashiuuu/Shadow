import pytest

import run_test

@pytest.mark.timeout(2)
def test_exit():
    run_test.run_test_command("exit")

@pytest.mark.timeout(2)
def test_var():
    run_test.run_test_command("PWD=1")

@pytest.mark.timeout(2)
def test_var_display():
    run_test.run_test_command("echo \"$PWD\"")

@pytest.mark.timeout(2)
def test_function():
    run_test.run_test_command("foo() { echo this is inside a command block; }")

@pytest.mark.timeout(2)
def test_echo_tr():
    run_test.run_test_command("{ echo a; echo b; } | tr b h")

@pytest.mark.timeout(2)
def test_cd_point_point_slash():
    run_test.run_test_command("cd ../")
    run_test.run_test_command("ls")

@pytest.mark.timeout(2)
def test_cd_slash():
    run_test.run_test_command("cd /")
    run_test.run_test_command("ls")

@pytest.mark.timeout(2)
def test_cd_wrong_path():
    run_test.run_test_command("cd jefnzejknf")
    run_test.run_test_command("ls")

    