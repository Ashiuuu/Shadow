#include "parser.h"
#include "lexer.h"

// Grammar :
//   list '\n'
// | list EOF
// | '\n'
// | EOF
enum parser_status parse_input(FILE *input)
{
    // for now:
    //   simple_command '\n'
    // | simple_command EOF
    // | '\n'
    // | EOF

    return PARSER_OK;
}

// Grammar :
//   (prefix)+
// | (prefix)* (element)+
enum parser_status parser_simple_command(FILE *input)
{
    // for nowm simple command is just WORD+ ie 'ls /bin' or 'pwd' 
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
enum parser_status parse_shell_command(FILE *input)
{
    // just if for now
    
    return PARSER_OK;
}

// Grammar :
// if compound_list  then compound_list [else_clause] fi
enum parser_status parse_if(FILE *input)
{
    return PARSER_OK;
}

// Grammar :
//   else compound_list
// | elif compound_list then compound_list [else_clause]
enum parser_status parse_else(FILE *input)
{
    return PARSER_OK;
}
