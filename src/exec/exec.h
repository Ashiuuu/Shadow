#pragma once

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct ast_node_command
{
    char **args;
};

struct ast_node_command *new_command_node(char **args);
void free_command_node(struct ast_node_command *node);
int exec_command_node(struct ast_node_command *node);
