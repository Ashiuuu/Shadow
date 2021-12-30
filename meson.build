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
cflags = ['-D_GNU_SOURCE', '-D_POSIX_C_SOURCE=200809L']
add_project_arguments(cflags, language: 'c')

incdirs = [
    include_directories('src/exec'),
    include_directories('src/io'),
    include_directories('src/lexer'),
    include_directories('src/parser'),
    include_directories('src/utils'),
]

lexer_files = [
    'src/lexer/tokens.c',
    'src/lexer/lexer.c',
    'src/lexer/word_lexer.c',
    'src/lexer/keyword_lexer.c',
]

parser_files = [
    'src/parser/parser.c',
    'src/parser/if_else_parser.c',
]

exec_files = [
    'src/exec/exec.c',
    'src/exec/command_node.c',
    'src/exec/list_node.c',
    'src/exec/echo.c',
]

common = lexer_files + parser_files + exec_files + [
    'src/io/io.c',
    'src/utils/utils.c',
]

test_files = [
    'test/io_test/io_test.c',
    'test/lexer_test/word_lexer_test.c',
    'test/lexer_test/lexer_test.c',
    'test/lexer_test/keyword_lexer_test.c',
]

executable(
    '42sh',
    common + ['src/main.c'],
    include_directories: incdirs
)

executable(
    'token_printer',
    common + ['src/token_printer.c'],
    include_directories: incdirs
)

executable(
    'ast_printer',
    common + ['src/ast_printer.c'],
    include_directories: incdirs
)

executable(
    'test_suite',
    common + test_files,
    include_directories: incdirs,
    objects: '/usr/lib/libcriterion.so'
    #objects: run_command('find', '/', '-name', 'libcriterion.so', '-print', '-quit').stdout().strip()
)
