project(
    '42sh',
    'c',
    version : '1.0',
    default_options: [
        'c_std=c99',
        'warning_level=3',
        'werror=true',
    ],
)
cflags=['']
add_project_arguments(cflags, language: 'c')

incdirs = [
    include_directories('src/exec'),
    include_directories('src/io'),
    include_directories('src/lexer'),
    include_directories('src/parser'),
]

common = [
    'src/exec/exec.c',
    'src/io/io.c',
    'src/lexer/lexer.c',
    'src/parser/parser.c',
]

executable(
    '42sh',
    common + ['src/main.c'],
    include_directories: incdirs
)

executable(
    'test_suite',
    common + ['test/io_test/io_test.c'],
    include_directories: incdirs
)
