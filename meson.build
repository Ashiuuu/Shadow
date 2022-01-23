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
cflags = ['-D_POSIX_C_SOURCE=200809L']
add_project_arguments(cflags, language: 'c')

ldlibs = ['-lasan']
add_project_link_arguments(ldlibs, language: 'c')


incdirs = [
    include_directories('src/exec'),
    include_directories('src/io'),
    include_directories('src/lexer'),
    include_directories('src/parser'),
    include_directories('src/utils'),
    include_directories('src/variables'),
]

lexer_files = [
    'src/lexer/tokens.c',
    'src/lexer/lexer.c',
    'src/lexer/lexer2.c',
    'src/lexer/lexer3.c',
    'src/lexer/word_lexer.c',
    'src/lexer/keyword_lexer.c',
    'src/lexer/sing_quote_lexer.c',
    'src/lexer/double_quote_lexer.c',
    'src/lexer/io_number_lexer.c',
    'src/lexer/general_lexer.c',
    'src/lexer/assignment_word_lexer.c',
]

parser_files = [
    'src/parser/parser.c',
    'src/parser/if_else_parser.c',
    'src/parser/redirection_parser.c',
    'src/parser/while_parser.c',
    'src/parser/until_parser.c',
    'src/parser/pipe_parser.c',
    'src/parser/and_or_parser.c',
    'src/parser/parse_command.c',
]

exec_files = [
    'src/exec/exec.c',
    'src/exec/command_node.c',
    'src/exec/list_node.c',
    'src/exec/echo.c',
    'src/exec/cd.c',
    'src/exec/if_node.c',
    'src/exec/redirec_nodes.c',
    'src/exec/redirections.c',
    'src/exec/while_node.c',
    'src/exec/until_node.c',
    'src/exec/pipe_node.c',
    'src/exec/and_or_node.c',
    'src/exec/variable_exec.c',
    'src/exec/assignment_node.c',

    'src/variables/variables.c',
    'src/variables/variables2.c',
]

printer_files = [
    'src/printer/printer.c',
]

file_input_files = [
    'src/script/file_input.c',
]

interactive_files = [
    'src/interactive/interactive.c',
]

common = lexer_files + parser_files + exec_files + printer_files + file_input_files + interactive_files + [
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
    #objects: '/usr/lib/libcriterion.so'
    objects: run_command('find', '/nix', '-name', 'libcriterion.so', '-print', '-quit').stdout().strip()
)

if get_option('doc')
    subdir('doc')
endif
