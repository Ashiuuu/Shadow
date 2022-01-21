#pragma once

#include <stdio.h>
#include <string.h>

#include "exec.h"
#include "lexer.h"

/**
 * @brief enum with parser status
 *
 * parser status lists.
 */
enum parser_status
{
    /// we got a syntax error
    PARSER_ERROR,
    /// parsing went good and we parsed something
    PARSER_FOUND,
    /// nothing found, but no error either
    PARSER_OK,
};

/**
 * @brief Token redirec
 *
 * This function checks if the token is a redirect token.
 *
 * @param type
 * @return int
 */
int is_redirec_token(enum token_type type);

/**
 * @brief A parser that parses a list of tokens
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param lexer
 * @return enum parser_status
 */
enum parser_status parse_input(struct ast_node **ast, struct lexer *lexer);

/**
 * @brief A parser that parses a list of simple command token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parser_simple_command(struct ast_node **ast,
                                         struct lexer *input);

/**
 * @brief A parser that parses a list of list token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_list(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of compund list token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_compound_list(struct ast_node **ast,
                                       struct lexer *input);

/**
 * @brief A parser that parses a list of else clause token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_else_clause(struct ast_node **ast,
                                     struct lexer *input);

/**
 * @brief A parser that parses a list of rule if token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_rule_if(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of rule while token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_rule_while(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of rule until token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_rule_until(struct ast_node **ast, struct lexer *input);
/**
 * @brief A parser that parses a list of do group token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_do_group(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of pipeline token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_pipeline(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of and or token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_and_or(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of redirection token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param red
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_redirection(struct redirection **red,
                                     struct lexer *input);

/**
 * @brief A parser that parses a list of command token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_command(struct ast_node **ast, struct lexer *input);

/**
 * @brief A parser that parses a list of shell command token
 *
 * A list of tokens is parsed, the function returns an enum depending on whether
 * everything went well.
 *
 * @param ast
 * @param input
 * @return enum parser_status
 */
enum parser_status parse_shell_command(struct ast_node **ast,
                                       struct lexer *input);

