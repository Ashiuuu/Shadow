#include "parser.h"

// Grammar :
//   list '\n'
// | list EOF
// | '\n'
// | EOF
enum parser_status parse_input(struct lexer *input)
{
    // for now:
    //   simple_command '\n'
    // | simple_command EOF
    // | '\n'
    // | EOF

    input = input;

    return PARSER_OK;
}

// Grammar :
//   (prefix)+
// | (prefix)* (element)+
enum parser_status parser_simple_command(struct lexer *input)
{
    // for nowm simple command is just WORD+ ie 'ls /bin' or 'pwd' 
    input = input;
    return PARSER_OK;
}

// Grammar :
//   '{' compound_list '}'
// | '(' compound_list ')'
// | rule_for
// | rule_while
// | rule_until
// | rule_case
// | rule_if
enum parser_status parse_shell_command(struct lexer *input)
{
    // just if for now
    input = input;

    return PARSER_OK;
}

// Grammar :
// if compound_list  then compound_list [else_clause] fi
enum parser_status parse_if(struct lexer *input)
{
    input = input;

    return PARSER_OK;
}

// Grammar :
//   else compound_list
// | elif compound_list then compound_list [else_clause]
enum parser_status parse_else(struct lexer *input)
{
    input = input;

    return PARSER_OK;
}
