project('42sh', 'c', default_options: [
    'c_std=c99',
    'warning_level=3',
])


all_sources = []
all_sources += 'main.c'

subdir('lexer')
subdir('parser')
subdir('exec')

executable('42sh', all_sources)
