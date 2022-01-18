#pragma once

#include <stdio.h>
#include <string.h>

#include "exec.h"
#include "lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_ERROR
};

int is_redirec_token(enum token_type type);

enum parser_status parse_input(struct ast_node **ast, struct lexer *lexer);
enum parser_status parser_simple_command(struct ast_node **ast,
                                         struct lexer *input);
enum parser_status parse_command_list(struct ast_node **ast,
                                      struct lexer *input);
enum parser_status parse_list(struct ast_node **ast, struct lexer *input);
enum parser_status parse_compound_list(struct ast_node **ast,
                                       struct lexer *input);

enum parser_status parse_else_clause(struct ast_node **ast,
                                     struct lexer *input);
enum parser_status parse_rule_if(struct ast_node **ast, struct lexer *input);
enum parser_status parse_rule_while(struct ast_node **ast, struct lexer *input);
enum parser_status parse_rule_until(struct ast_node **ast, struct lexer *input);
enum parser_status parse_do_group(struct ast_node **ast, struct lexer *input);

enum parser_status parse_pipeline(struct ast_node **ast, struct lexer *input);

enum parser_status parse_redirection(struct redirection **red,
                                     struct lexer *input);

enum parser_status parse_command(struct ast_node **ast, struct lexer *input);
enum parser_status parse_shell_command(struct ast_node **ast,
                                       struct lexer *input);