import pytest

import run_test

@pytest.mark.timeout(2)
def test_exit():
    run_test.run_test_command("exit")

@pytest.mark.timeout(2)
def test_test_var():
    run_test.run_test_command("PWD=1")

@pytest.mark.timeout(2)
def test_test_var_display():
    run_test.run_test_command("echo \"$PWD\"")

@pytest.mark.timeout(2)
def test_test_function():
    run_test.run_test_command("foo() { echo this is inside a command block; }")

@pytest.mark.timeout(2)
def test_test_function():
    run_test.run_test_command("{ echo a; echo b; } | tr b h")
    