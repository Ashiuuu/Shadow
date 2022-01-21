#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tokens.h"

/**
 * @brief Command node for the AST
 *
 * Simple command node for the AST. It contains a list of argument to be executed (including name of the command/executable)
 */
struct ast_node_command
{
    /// Arguments of the command
    char **args;
};

/**
 * @brief List node for the AST
 *
 * Simple list node for the AST. It is a dynamically allocated, and contains a set of nodes to be executed.
 */
struct ast_node_list
{
    /// AST Nodes vector
    struct ast_node **nodes;
    /// Length of the nodes vector
    size_t len; 
    /// Capacity of the vector, to keep track of the memory allocation
    size_t capacity; 
};

struct ast_node_if
{
    struct ast_node *condition;
    struct ast_node *body_list;
    struct ast_node *elif;
};

struct ast_node_while
{
    struct ast_node *condition;
    struct ast_node *body_list;
};

struct ast_node_until
{
    struct ast_node *condition;
    struct ast_node *body_list;
};

struct redirection
{
    int source_fd; // file descriptor of the source
    int replaced_fd; // file descriptor to be replaces (destination)
    int duped_fd; // holds the replaced_fd to later undo the redirection
};

struct ast_node_redirec_list
{
    struct redirection **redirections; // list of redirections, ex: "2>&3 1>&2
                                       // 3>&1" (swaps stderr and stdout)
    size_t capacity;
    size_t len;
    struct ast_node *child; // node concerned by the redirection, swap back to
                            // normal after executing
};

struct ast_node_pipe
{
    struct ast_node *left;
    struct ast_node *right;
    int negated;
};

struct ast_node_and_or
{
    struct ast_node *left;
    struct ast_node *right;
    enum token_type type;
};

enum node_type
{
    NODE_COMMAND,
    NODE_LIST,
    NODE_IF,
    NODE_REDIREC_LIST,
    NODE_WHILE,
    NODE_UNTIL,
    NODE_PIPE,
    NODE_AND_OR,
};

union ast_data
{
    struct ast_node_command ast_command;
    struct ast_node_list ast_list;
    struct ast_node_if ast_if;
    struct ast_node_redirec_list ast_redirec_list;
    struct ast_node_while ast_while;
    struct ast_node_until ast_until;
    struct ast_node_pipe ast_pipe;
    struct ast_node_and_or ast_and_or;
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
struct redirection *new_redirection(char *source, char *replaced,
                                    enum token_type type);
void free_redirection(struct redirection *r);
int execute_redirection(struct redirection *r);
int undo_redirection(struct redirection *r);

struct ast_node *new_redirec_list_node();
void free_redirec_list_node(struct ast_node *node);
void push_redirec_list_node(struct ast_node *node, struct redirection *add);
int exec_redirec_list_node(struct ast_node *node);

// while loop
struct ast_node *new_while_node();
void free_while_node(struct ast_node *node);
int exec_while_node(struct ast_node *node);

// until loop
struct ast_node *new_until_node();
void free_until_node(struct ast_node *node);
int exec_until_node(struct ast_node *node);

// pipe
struct ast_node *new_pipe_node();
void free_pipe_node(struct ast_node *node);
int exec_pipe_node(struct ast_node *node);

// and_or
struct ast_node *new_and_or_node();
void free_and_or_node(struct ast_node *node);
int exec_and_or_node(struct ast_node *node);

// built-ins
int echo(struct ast_node *node);

// utility

int is_digit(char c);
