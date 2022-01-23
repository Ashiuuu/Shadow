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

    int nflag = 0;
    int eflag = 0;
    int stop_options = 0;

    for (size_t i = 1; node->data.ast_command.args_strings[i] != NULL; ++i)
    {
        char *curr = node->data.ast_command.args_strings[i];
        if (stop_options == 0 && strcmp(curr, "-n") == 0)
            nflag = 1;
        else if (stop_options == 0 && (strcmp(curr, "-e") == 0))
            eflag = 1;
        else if (stop_options == 0 && (strcmp(curr, "-ne") == 0))
        {
            eflag = 1;
            nflag = 1;
        }
        else
        {
            stop_options = 1;
            if (eflag == 0)
            {
                for (size_t j = 0; curr[j] != '\0'; ++j)
                    printf("%c", curr[j]);

                if (node->data.ast_command.args_strings[i + 1] != NULL)
                    printf(" ");
            }
            else
            {
                for (size_t k = 0; curr[k] != '\0'; ++k)
                {
                    if (curr[k] == '\\')
                    {
                        switch (curr[k + 1])
                        {
<<<<<<< HEAD
                        case 'n':
                            printf("\n");
                            break;
                        case 't':
                            printf("\t");
                            break;
                        default:
                            printf("%c", curr[k + 1]);
=======
                        case 'n':
                            printf("\n");
                            break;
                        case 't':
                            printf("\t");
                            break;
                        default:
                            printf("%c", curr[k + 1]);
>>>>>>> 3ce8ee2ac054f0ec3303069d52544374cb260013
                        }
                        k++;
                    }
                    else
                        printf("%c", curr[k]);
                }
                if (node->data.ast_command.args_strings[i + 1] != NULL)
                    printf(" ");
            }
        }
    }

    if (nflag == 0)
        printf("\n");
    return 0;
}
