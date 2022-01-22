#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "variables.h"
#include "utils.h"

struct linked_list *new_linked_list()
{
    struct linked_list *ret = xmalloc(sizeof(struct linked_list));
    ret->next = NULL;
    ret->key = NULL;
    ret->value = NULL;

    return ret;
}

void free_linked_list(struct linked_list *list)
{
    if (list != NULL)
    {
        if (list->key != NULL)
            free(list->key);
        if (list->value != NULL)
            free(list->value);
        if (list->next != NULL)
            free_linked_list(list->next);
        free(list);
    }
}

void push_linked_list(struct linked_list *list, char *name, char *value)
{
    if (list == NULL)
        return;

    if (list->key != NULL) // if the current node already has an entry
    {
        if (strcmp(list->key, name) == 0) // key is already taken
        {
            free(list->value);
            list->value = strdup(value);
            return;
        }
        if (list->next != NULL) // if there is a next node
        {
            push_linked_list(list->next, name, value); // push the variable to that next node
            return;
        }
        // else, current node is not available but no next node
        struct linked_list *new = new_linked_list();
        new->key = strdup(name);
        new->value = strdup(value);
        list->next = new;
        return; // variable is pushed, all good
    }
    list->key = strdup(name);
    if (list->value != NULL) // no key but value for some reason ??
        free(list->value);
    list->value = strdup(value);
}

char *get_linked_list(struct linked_list *list, char *name)
{
    if (list == NULL)
        return NULL;

    if (list->key != NULL)
    {
        if (strcmp(list->key, name) == 0)
        {
            return list->value;
        }
    }

    // key was NULL, check next node
    if (list->next != NULL)
    {
        return get_linked_list(list->next, name);
    }

    return NULL; // no key and no next node, so no variable
}
