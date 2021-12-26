#include <errno.h>

#include "exec.h"
#include "utils.h"

// char **args = [ "test", "salut", NULL ]
struct ast_node *new_command_node(char **args)
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_COMMAND;
    ret->data.ast_command.args = xcalloc(array_len(args) + 1, sizeof(char *));
    for (size_t i = 0; args[i] != NULL; ++i)
    {
        ret->data.ast_command.args[i] = strdup(args[i]);
    }
    ret->data.ast_command.args[array_len(args)] = NULL;
    return ret;
}

void free_command_node(struct ast_node *node)
{
    if (node->type != NODE_COMMAND)
    {
        fprintf(stderr, "trying to free node of wrong type (command)");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_command.args != NULL)
        {
            for (size_t i = 0; node->data.ast_command.args[i] != NULL; ++i)
                free(node->data.ast_command.args[i]);
            free(node->data.ast_command.args);
        }
        free(node);
    }
}

int exec_command_node(struct ast_node *node)
{
    if (node->type != NODE_COMMAND)
    {
        fprintf(stderr, "trying to exec node of wrong type (command)");
        return -1;
    }
    int status;

    if (strcmp(node->data.ast_command.args[0], "echo") == 0)
    {
        return echo(node);
    }

    pid_t child = fork();
    if (child == -1)
    {
        fprintf(stderr, "Could not fork process\n");
        abort();
    }

    if (child == 0)
    {
        // child process
        execvp(node->data.ast_command.args[0], node->data.ast_command.args);
        fprintf(stderr, "Could not execute %s\n", node->data.ast_command.args[0]);
        return -1;
    }
    else
    {
        // parent process
        wait(&status); // wait for child
    }

    return status;
}
