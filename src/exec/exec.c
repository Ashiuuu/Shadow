#include "exec.h"

#include <stdlib.h>

#include "utils.h"

void free_node(struct ast_node *node)
{
    if (node == NULL)
        return;
    switch (node->type)
    {
    case NODE_COMMAND:
        free_command_node(node);
        break;
    case NODE_LIST:
        free_list_node(node);
        break;
    case NODE_IF:
        free_if_node(node);
        break;
    case NODE_REDIREC_LIST:
        free_redirec_list_node(node);
        break;
    case NODE_WHILE:
        free_while_node(node);
        break;
    case NODE_UNTIL:
        free_until_node(node);
        break;
    case NODE_PIPE:
        free_pipe_node(node);
        break;
    case NODE_AND_OR:
        free_and_or_node(node);
        break;
    default:
        fprintf(stderr, "unknown node type (free_node)\n");
    }
}

int exec_node(struct ast_node *node)
{
    switch (node->type)
    {
    case NODE_COMMAND:
        return exec_command_node(node);
    case NODE_LIST:
        return exec_list_node(node);
    case NODE_IF:
        return exec_if_node(node);
    case NODE_REDIREC_LIST:
        return exec_redirec_list_node(node);
    case NODE_WHILE:
        return exec_while_node(node);
    case NODE_UNTIL:
        return exec_until_node(node);
    case NODE_PIPE:
        return exec_pipe_node(node);
    case NODE_AND_OR:
        return exec_and_or_node(node);
    default:
        fprintf(stderr, "unknown node type (exec_node)\n");
        return -1;
    }
}
