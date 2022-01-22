import pytest

import run_test

@pytest.mark.timeout(2)
def test_if_simple_comma():
    run_test.run_test_command("if echo a; then echo b; else echo c; fi")

@pytest.mark.timeout(2)
def test_if_simple_without_comma():
    run_test.run_test_command("if echo a then echo b else echo c fi")

@pytest.mark.timeout(2)
def test_if_wrong_syntax():
    run_test.run_test_command("if echo a; then echo couille;")
