#pragma once

struct linked_list
{
    struct linked_list *next;
    char *key;
    char *value;
};

struct linked_list *variables;

struct linked_list *new_linked_list();
void free_linked_list(struct linked_list *list);
void push_linked_list(struct linked_list *list, char *name, char *value);
char *get_linked_list(struct linked_list *list, char *name);