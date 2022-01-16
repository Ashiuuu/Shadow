import subprocess

def test_hello():
    result = subprocess.run(["./42sh", "-c", "echo Hello"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    assert result== 'Hello\n'