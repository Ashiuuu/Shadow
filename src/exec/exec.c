#include <errno.h>

#include "exec.h"
#include "utils.h"

// char **args = [ "test", "salut", NULL ]
struct ast_node_command *new_command_node(char **args)
{
    struct ast_node_command *ret = xmalloc(sizeof(struct ast_node_command));
    ret->args = xcalloc(array_len(args) + 1, sizeof(char *));
    for (size_t i = 0; args[i] != NULL; ++i)
    {
        ret->args[i] = strdup(args[i]);
    }
    ret->args[array_len(args)] = NULL;
    return ret;
}

void free_command_node(struct ast_node_command *node)
{
    if (node->args != NULL)
    {
        for (size_t i; node->args[i] != NULL; ++i)
            free(node->args[i]);
    }

    free(node);
}

int exec_command_node(struct ast_node_command *node)
{
    int status;

    pid_t child = fork();
    if (child == -1)
    {
        fprintf(stderr, "Could not fork process\n");
        abort();
    }

    if (child == 0)
    {
        // child process
        //char *args[] = { "bash", "-c", "echo test", NULL };
        //execvp("bash", args);
        execvp(node->args[0], node->args);
        printf("error: %d\n", errno);
        printf("%d\n", EACCES);
        printf("EFAULT: %d\n", EFAULT);
        printf("%d\n", EIO);
        printf("%d\n", ELOOP);
        printf("%d\n", E2BIG);
        printf("%d\n", EAGAIN);
        printf("%d\n", EINVAL);
        printf("%d\n", EISDIR);
        printf("%d\n", ELIBBAD);
        printf("%d\n", EMFILE);
        printf("%d\n", ENAMETOOLONG);
        printf("%d\n", ENFILE);
        printf("ENOENT: %d\n", ENOENT);
        printf("%d\n", ENOEXEC);
        printf("%d\n", ENOMEM);
        printf("%d\n", ENOTDIR);
        printf("%d\n", EPERM);
        printf("%d\n", ETXTBSY);
        fprintf(stderr, "Could not execute %s\n", node->args[0]);
    }
    else
    {
        // parent process
        /*pid_t wait_pid = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
        if (wait_pid == -1)
        {
            fprintf(stderr, "wait pid error\n");
            abort();
        }*/

        wait(&status); // wait for child
    }

    return status;
}
