import run_test_var
from test.functional.run_test import run_test_command

def test_special_name_scrypt():
    run_test_var.run_test_command("test/functional/variable/var.sh")

def test_special_nb_parameter():
    run_test_var.run_test_command("test/functional/variable/var_param_nb.sh")

def test_special_UID_and_RANDOM():
    run_test_var.run_test_command("test/functional/variable/var_random.sh")

def test_number_var():
    run_test_var.run_test_command("test/functional/variable/var_number.sh")