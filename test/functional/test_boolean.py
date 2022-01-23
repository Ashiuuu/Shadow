import pytest

import run_test

@pytest.mark.timeout(2)
def test_true():
    run_test.run_test_command("true")

@pytest.mark.timeout(2)
def test_false():
    run_test.run_test_command("false")

@pytest.mark.timeout(2)
def test_true_pipe_false():
    run_test.run_test_command("true | false")

@pytest.mark.timeout(2)
def test_false_pipe_true():
    run_test.run_test_command("false | true")

@pytest.mark.timeout(2)
def test_not_true():
    run_test.run_test_command("! true")

@pytest.mark.timeout(2)
def test_not_false():
    run_test.run_test_command("! false")

@pytest.mark.timeout(2)
def test_not_true_pipe_not_false():
    run_test.run_test_command("! true | ! false")

@pytest.mark.timeout(2)
def test_true_double_esperluette_false():
    run_test.run_test_command("true && false")

@pytest.mark.timeout(2)
def test_not_true_esperluette_false():
    run_test.run_test_command("! true && ! false")
