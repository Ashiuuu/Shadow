#include <errno.h>
#include <stdio.h>

#include "exec.h"
#include "utils.h"
#include "variables.h"

size_t token_array_len(struct token **a)
{
    size_t ret = 0;
    for (size_t i = 0; a[i] != NULL; ++i)
        ret++;
    return ret;
}

struct ast_node *new_command_node(struct token **args)
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    size_t arr_len = token_array_len(args);
    ret->type = NODE_COMMAND;
    ret->data.ast_command.args_strings = NULL;
    ret->data.ast_command.args = xcalloc(arr_len + 1, sizeof(struct token *));
    for (size_t i = 0; args[i] != NULL; ++i)
    {
        ret->data.ast_command.args[i] = token_dup(args[i]);
        token_free(args[i]);
    }
    free(args);
    ret->data.ast_command.args[arr_len] = NULL;
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
                token_free(node->data.ast_command.args[i]);
            free(node->data.ast_command.args);
        }
        if (node->data.ast_command.args_strings != NULL)
        {
            for (size_t i = 0; node->data.ast_command.args_strings[i] != NULL;
                 ++i)
                free(node->data.ast_command.args_strings[i]);
            free(node->data.ast_command.args_strings);
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

    // loop to expand variables
    size_t len = 0;
    for (size_t i = 0; node->data.ast_command.args[i] != NULL; ++i)
    {
        if (node->data.ast_command.args[i]->type == TOKEN_WORDS)
        {
            len++;
            continue;
        }
        else if (node->data.ast_command.args[i]->type != TOKEN_EXPAND)
        {
            // ?????
            fprintf(stderr,
                    "[FATAL] Got non word or expand token into command node\n");
            abort();
        }
        char *replaced =
            variable_search_and_replace(node->data.ast_command.args[i]->value);
        if (replaced != NULL)
            node->data.ast_command.args[i]->value = replaced;
        len++;
    }

    // convert tokens into strings
    node->data.ast_command.args_strings = xmalloc(sizeof(char *) * (len + 1));
    for (size_t i = 0; i < len; ++i)
    {
        node->data.ast_command.args_strings[i] =
            strdup(node->data.ast_command.args[i]->value);
    }
    node->data.ast_command.args_strings[len] = NULL;

    if (strcmp(node->data.ast_command.args_strings[0], "echo") == 0)
    {
        status = echo(node);
        variable_push_int("?", status);
        return status;
    }
    if (strcmp(node->data.ast_command.args_strings[0], "cd") == 0)
    {
        status = cd(node);
        variable_push_int("?", status);
        return status;
    }
    if (strcmp(node->data.ast_command.args_strings[0], "exit") == 0)
    {
        int return_status;
        if (node->data.ast_command.args_strings[1] == NULL)
            return_status = 0;
        else
            return_status = atoi(node->data.ast_command.args_strings[1]);
        exit(return_status);
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
        execvp(node->data.ast_command.args_strings[0],
               node->data.ast_command.args_strings);
        fprintf(stderr, "Could not execute %s\n",
                node->data.ast_command.args_strings[0]);
        exit(127);
        // return -1;
    }
    else
    {
        // parent process
        wait(&status); // wait for child
    }
    variable_push_int("?", WEXITSTATUS(status));
    return WEXITSTATUS(status);
}
