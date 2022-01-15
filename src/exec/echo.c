#include <getopt.h>
#include <unistd.h>

#include "exec.h"
#include "utils.h"

int echo(struct ast_node *node)
{
    if (node->type != NODE_COMMAND)
    {
        fprintf(stderr, "trying to call echo on non command node\n");
        return -1;
    }
    struct ast_node_command command = node->data.ast_command;
    if (node->data.ast_command.args != NULL
        && strcmp(node->data.ast_command.args[0], "echo") != 0)
    {
        fprintf(stderr, "trying to call echo on non echo command node\n");
        return -1;
    }

    int optind_backup = optind;

    int opt;
    int nflag = 0;
    int eflag = 0;

    size_t args_len = array_len(command.args);
    optind = 1;
    opt = getopt(args_len, command.args, "ne");
    while (opt != -1)
    {
        switch (opt)
        {
        case 'n':
            nflag = 1;
            break;
        case 'e':
            eflag = 1;
            break;
        case '?':
            printf("echo: Unknown option character\n");
            break;
        default:
            fprintf(stderr, "error while parsing echo options\n");
            abort();
        }
        opt = getopt(args_len, command.args, "ne");
    }
    eflag = eflag;

    for (size_t i = optind; command.args[i] != NULL; i++)
    {
        char *string = command.args[i];
        if (eflag == 0)
        {
            for (size_t j = 0; string[j] != '\0'; ++j)
            {
                printf("%c", string[j]);
                /*printf("  %d - ", string[j]);
                printf("%c\n", string[j]);*/
            }
        }
        else
        {
            printf("%s", string);
        }
        if (nflag == 0)
            printf("\n");
    }

    optind = optind_backup;

    return 0;
}