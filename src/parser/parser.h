#pragma once

#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "exec.h"

enum parser_status
{
    PARSER_OK,
    PARSER_ERROR
};

enum parser_status parse_input(struct ast_node **ast, struct lexer *lexer);
enum parser_status parser_simple_command(struct ast_node **ast, struct lexer *input);
enum parser_status parse_command_list(struct ast_node **ast, struct lexer *input);
enum parser_status parse_list(struct ast_node **ast, struct lexer *input);
enum parser_status parse_compound_list(struct ast_node **ast, struct lexer *input);

enum parser_status parse_else_clause(struct ast_node **ast, struct lexer *input);
enum parser_status parse_rule_if(struct ast_node **ast, struct lexer *input);