#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "exec.h"
#include "utils.h"

/**
 * @brief print ast function
 *
 * This function displays in the standard output an ast.
 *
 * @param node
 * @param type
 */
void print_ast(struct ast_node *node, char *type);

/**
 * @brief print ast command function
 *
 * This function displays in the standard output an ast.
 *
 * @param ast_command
 */
void print_ast_command(struct ast_node_command ast_command);

/**
 * @brief print ast if
 *
 * This function displays in the standard output an ast.
 *
 * @param ast_if
 * @param type
 */
void print_ast_if(struct ast_node_if ast_if, char *type);

/**
 * @brief print ast redir
 *
 * This function displays in the standard output an ast.
 *
 * @param ast_redir
 */
void print_ast_redir(struct ast_node_redirec_list ast_redir);