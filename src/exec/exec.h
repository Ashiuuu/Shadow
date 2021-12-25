#pragma once

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct ast_node_command
{
    char **args;
};

struct ast_node_list
{
    struct ast_node **nodes;
    size_t len;
    size_t capacity;
};

enum node_type {
    NODE_COMMAND,
    NODE_LIST,
};

union ast_data
{
    struct ast_node_command ast_command;
    struct ast_node_list ast_list;
};

struct ast_node
{
    enum node_type type;
    union ast_data data;
};

// general purpose
void free_node(struct ast_node *node);
int exec_node(struct ast_node *node);

// command node
struct ast_node *new_command_node(char **args);
void free_command_node(struct ast_node *node);
int exec_command_node(struct ast_node *node);

// list node
struct ast_node *new_list_node();
void list_node_push(struct ast_node *node, struct ast_node *added);
void free_list_node(struct ast_node *node);
int exec_list_node(struct ast_node *node);
