import pytest

import run_test

@pytest.mark.timeout(2)
def test_alias():
    run_test.run_test_command("alias funcdec='foo('funcdec) { echo ok; }")
    run_test.run_test_command("foo")



    