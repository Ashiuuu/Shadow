#include <getopt.h>
#include <unistd.h>

#include "exec.h"
#include "utils.h"

int cd(struct ast_node *node)
{
    if (node->type != NODE_COMMAND)
    {
        fprintf(stderr, "trying to call cd on non command node\n");
        return 1;
    }

    if (node->data.ast_command.args != NULL
        && strcmp(node->data.ast_command.args[0], "cd") != 0)
    {
        fprintf(stderr, "trying to call cd on non cd command node\n");
        return 1;
    }

    char *path = node->data.ast_command.args[1];
    // if path == NULL
    //     cd to home (~/ == /home/[user])

    int ret = chdir(path);

    if (ret < 0)
    {
        fprintf(stderr, "cd: aucun fichier au dossier de ce type: %s\n", path);
        return 1;
    }

    return ret;
}
