#include <stdio.h>
#include <stdlib.h>

#include "variables.h"
#include "utils.h"

void init_variables()
{
    push_linked_list(variables, "?", "0");
    /*char *uid = xmalloc(sizeof(char) * 5);
    sprintf(uid, "%lu", getuid);
    push_linked_list(variables, "UID", uid);*/
    variable_push_int("$", getpid());
}

void init_positional_arguments(char **args)
{
    size_t len = 0;

    char *all_args = xcalloc(1, sizeof(char));
    size_t all_cap = 1;

    for (size_t i = 0; args[i] != NULL; ++i)
    {
        char *pos = xmalloc(sizeof(char) * 3);
        sprintf(pos, "%ld", i);
        push_linked_list(variables, pos, args[i]);
        free(pos);
        len++;

        all_cap = all_cap + strlen(args[i]);
        all_args = xrealloc(all_args, sizeof(char) * all_cap);
        all_args = strcat(all_args, args[i]);
    }

    char *all_args2 = strdup(all_args);
    push_linked_list(variables, "@", all_args);
    free(all_args);
    push_linked_list(variables, "*", all_args2);
    free(all_args2);
    char *len_string = xmalloc(sizeof(char) * 3);
    sprintf(len_string, "%ld", len);
    push_linked_list(variables, "#", len_string);
    free(len_string);    
}

void variable_push_int(char *name, int a)
{
    char *temp = xcalloc(15, sizeof(char));
    sprintf(temp, "%d", a);
    push_linked_list(variables, name, temp);
    free(temp);
}

char *get_variable(char *name)
{
    if (strcmp(name, "RANDOM") == 0)
    {
        //variable_push_int("RANDOM", random());
        variable_push_int("RANDOM", rand_r());
        return get_linked_list(variables, "RANDOM");
    }
    return get_linked_list(variables, name);
}
