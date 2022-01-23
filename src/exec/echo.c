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
    if (node->data.ast_command.args_strings != NULL
            && strcmp(node->data.ast_command.args_strings[0], "echo") != 0)
    {
        fprintf(stderr, "trying to call echo on non echo command node\n");
        return -1;
    }

    int optind_backup = optind;

    int opt;
    int nflag = 0;
    int eflag = 0;
    int rflag = 0;

    size_t args_len = array_len(node->data.ast_command.args_strings);
    optind = 0;
    opterr = 0;
    int magic = 1;
    opt = getopt(args_len, node->data.ast_command.args_strings, "ne");
    while (opt != -1 && rflag !=1)
    {
        switch (opt)
        {
            case 'n':
                magic++;
                nflag = 1;
                break;
            case 'e':
                magic++;
                eflag = 1;
                break;
            case '?':
                rflag = 1;
                break;
            default:
                fprintf(stderr, "error while parsing echo options\n");
                abort();
        }
        opt = getopt(args_len, node->data.ast_command.args_strings, "ne");
    }

    optind = magic;

    if (rflag == 1 && eflag == 0)
    {
        size_t j = 1;
        if (nflag == 1)
            j++;
        for (; node->data.ast_command.args_strings[j] != NULL; ++j)
        {
            printf("%s", node->data.ast_command.args_strings[j]);
            if (node->data.ast_command.args_strings[j + 1] != NULL)
                printf(" ");
        }
        if (nflag == 0)
            printf("\n");
        return 0;
    }


    for (size_t i = optind; node->data.ast_command.args_strings[i] != NULL; i++)
    {
        char *string = node->data.ast_command.args_strings[i];
        if (eflag == 0)
        {
            for (size_t j = 0; string[j] != '\0'; ++j)
                printf("%c", string[j]);

            if (node->data.ast_command.args_strings[i + 1] != NULL)
                printf(" ");
        }
        else
        {
            for (size_t k = 0; string[k] != '\0'; ++k)
            {
                if (string[k] == '\\')
                {
                    switch (string[k + 1])
                    {
                        case 'n':
                            printf("\n");
                            break;
                        case 't':
                            printf("\t");
                            break;
                        default:
                            printf("%c", string[k + 1]);
                    }
                    k++;
                }
                else
                    printf("%c", string[k]);
            }
            if (node->data.ast_command.args_strings[i + 1] != NULL)
                printf(" ");
        }
    }
    if (nflag == 0)
        printf("\n");

    optind = optind_backup;

    return 0;
}
