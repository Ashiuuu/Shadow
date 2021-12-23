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

enum parser_status parse_input(struct ast_node_command *ast, struct lexer *lexer);
enum parser_status parser_simple_command(struct ast_node_command *ast, struct lexer *input);
