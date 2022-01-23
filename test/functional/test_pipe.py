import subprocess
import pytest

import run_test

@pytest.mark.timeout(2)
def test_pipe_single():
    run_test.run_test_command("echo a | echo b")

@pytest.mark.timeout(2)
def test_pipe_double():
    run_test.run_test_command("echo a | echo b | echo c")

@pytest.mark.timeout(2)
def test_pipe_triple():
    run_test.run_test_command("echo a | echo b | echo c | echo d")

@pytest.mark.timeout(2)
def test_pipe_wrong_syntax():
    run_test.run_test_command("echo a | echo b |")

@pytest.mark.timeout(4)
def test_pipe_word_cut():
    run_test.run_test_command("ls -l | wc")

