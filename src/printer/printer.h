#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "utils.h"
#include "exec.h"

void print_ast(struct ast_node *node);
void print_ast_command(struct ast_node_command ast_command);
void print_ast_if(struct ast_node_if ast_if);
void print_ast_redir(struct ast_node_redirec_list ast_redir);