#include "exec.h"
#include "utils.h"

struct ast_node *new_pipe_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_PIPE;
    ret->data.ast_pipe.left = NULL;
    ret->data.ast_pipe.right = NULL;
    ret->data.ast_pipe.negated = 0;

    return ret;
}

void free_pipe_node(struct ast_node *node)
{
    if (node->type != NODE_PIPE)
    {
        fprintf(stderr, "trying to free non pipe node\n");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_pipe.left != NULL)
            free_node(node->data.ast_pipe.left);
        if (node->data.ast_pipe.right != NULL)
            free_node(node->data.ast_pipe.right);
        free(node);
    }
}

int exec_pipe_node(struct ast_node *node)
{
    if (node->type != NODE_PIPE)
    {
        fprintf(stderr, "trying to execute non pipe node\n");
        return -1;
    }

    if (node->data.ast_pipe.left == NULL || node->data.ast_pipe.right == NULL)
    {
        fprintf(stderr, "missing operand [pipe exec]\n");
        return -1;
    }

    int return_status;

    // exec nodes
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork fail [pipe]\n");
        return -1;
    }
    if (pid == 0) // child
    {
        // create pipe
        int fds[2];
        pipe(fds);

        // fork and execute nodes
        pid_t child = fork();
        if (child < 0)
        {
            fprintf(stderr, "child fork fail [pipe]\n");
            return -1;
        }

        if (child == 0) // child
        {
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
            close(fds[1]);

            exit(exec_node(node->data.ast_pipe.right));
        }
        else // parent
        {
            dup2(fds[1], STDOUT_FILENO);
            close(fds[0]);
            close(fds[1]);

            exit(exec_node(node->data.ast_pipe.left));
        }
    }
    else // parent process
    {
        while (wait(&return_status) > 0)
            continue;
    }

    if (node->data.ast_pipe.negated == 0)
        return return_status;
    else
    {
        if (return_status == 0)
            return 1;
        else
            return 0;
    }
}