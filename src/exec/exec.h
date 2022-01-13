#pragma once

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

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

struct ast_node_if
{
    struct ast_node *condition;
    struct ast_node *body_list;
    struct ast_node *elif;
};

struct redirection
{
    char *io_number;
    enum token_type type;
    char *dest;
};

struct ast_node_redirec_list
{
    struct redirection **redirections; // list of redirections, ex: "2>&3 1>&2 3>&1" (swaps stderr and stdout)
    size_t capacity;
    size_t len;
    struct ast_node *child;         // node concerned by the redirection, swap back to normal after executing
}

enum node_type {
    NODE_COMMAND,
    NODE_LIST,
    NODE_IF,
    NODE_REDIREC_LIST,
};

union ast_data
{
    struct ast_node_command ast_command;
    struct ast_node_list ast_list;
    struct ast_node_if ast_if;
    struct ast_node_redirec_list ast_redirec_list;
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

// if node
struct ast_node *new_if_node();
void free_if_node(struct ast_node *node);
int exec_if_node(struct ast_node *node);

// redirections
struct redirection *new_redirection();
struct ast_node *new_redirec_list_node();
void free_redirection(struct redirection *r);
void free_redirec_list_node(struct ast_node *node);
void push_redirec_list_node(struct ast_node *node, struct redirection *add);
int exec_redirec_list_node(struct ast_node *node);

// built-ins
int echo(struct ast_node *node);
