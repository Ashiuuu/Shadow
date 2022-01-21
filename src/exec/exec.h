#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "tokens.h"

/**
 * @brief Command node for the AST
 *
 * Simple command node for the AST. It contains a list of argument to be
 * executed (including name of the command/executable)
 */
struct ast_node_command
{
    /// Arguments of the command
    char **args;
};

/**
 * @brief List node for the AST
 *
 * Simple list node for the AST. It is a dynamically allocated, and contains a
 * set of nodes to be executed.
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

/**
 * @brief If node for the AST
 *
 * AST Node that holds a if structure. It executes the condition node, and if
 * the result is 0, executes the body_list node. Else, execute the elif node
 */
struct ast_node_if
{
    /// Condition node. If no condition is present, the node behavior is that of
    /// a else case
    struct ast_node *condition;
    /// Body node. Contains a compound list, commands separated by ';' or '\n'
    /// characters
    struct ast_node *body_list;
    /// Optional elif node. Is either a 'elif' or a 'else'
    struct ast_node *elif;
};

/**
 * @brief While node for the AST
 *
 * AST Node that holds a while structure. It executes the condition node, and if
 * the result is 0, execute the body_list node. Repeat while the condition is
 * met
 */
struct ast_node_while
{
    /// Condition node
    struct ast_node *condition;
    /// Body node, a compound list (see if node for explanation)
    struct ast_node *body_list;
};

/**
 * @brief Until node for the AST
 *
 * AST Node that holds a until structure. It executes the condition node, and if
 * the result is not 0, execute the body_list node. Repeat while the condition
 * is met
 */
struct ast_node_until
{
    /// Condition node
    struct ast_node *condition;
    /// Body node, a compound list (see if node for explanation)
    struct ast_node *body_list;
};

/**
 * @brief Structure that holds a file descriptor redirection
 *
 * Holds a source file descriptor, and a file descriptor to be replaced. The
 * redirection is first executed, and the replaced FD is backed up in duped_fd.
 * When the redirection is undone, duped_fd is used to restore the file
 * descriptors to their original state.
 */
struct redirection
{
    /// File descriptor of the source, that is going to replace another file
    /// descriptor
    int source_fd;
    /// File descriptor to be replaced by the source
    int replaced_fd;
    /// Temporary file descriptor. Used after the execution of the structure to
    /// backup replaced_fd
    int duped_fd;
};

/**
 * @brief AST Node that holds a list of redirections to be executed
 *
 * The redirection list is dynamically allocated. At execution, the redirections
 * are executed bottom to top. After the child node execution, they are undone
 * top to bottom
 */
struct ast_node_redirec_list
{
    /// Vector of redirections
    struct redirection **redirections;
    /// Capacity of the redirections vector. Used to keep track of the memory
    /// allocation
    size_t capacity;
    /// Length of the redirections vector
    size_t len;
    /// Child node to be executed with the redirections applied
    struct ast_node *child;
};

/**
 * @brief AST node for the pipe
 *
 * The pipe connects the stdout file descriptor of the left node to the stdin
 * file descriptor of the right node to allow redirection between two commands.
 * The return status of the pipe is the return status of the right node. If the
 * pipe is preceeded by a '!', the return status is reversed
 */
struct ast_node_pipe
{
    /// Left AST node
    struct ast_node *left;
    /// Right AST node
    struct ast_node *right;
    /// Flag to keep track of the return status being negated or not
    int negated;
};

/**
 * @brief AST node for the and/or node
 *
 * Executes the left node. If the return status is 0, and the type of the node
 * is 'AND', executes the right node. If the return status is not 0 and the type
 * of the node is 'OR', execute the right node as well. Else, do not execute the
 * right node.
 */
struct ast_node_and_or
{
    /// Left node
    struct ast_node *left;
    /// Right node
    struct ast_node *right;
    /// Type of the node, either 'TOKEN_AND' or 'TOKEN_OR'
    enum token_type type;
};

/**
 * @brief Enum that holds the type of a node
 *
 * Used with the union 'ast_data' to get C polymorphism
 */
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

/**
 * @brief Union of different node types
 *
 * Contains one sub-type of AST node, used with the 'node_type' union to
 * differentiate
 */
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

/**
 * @brief General AST node struct
 *
 * Holds an AST node, used in all functions manipulating AST nodes. Different
 * node types are differentiated using the 'node_type' enum
 */
struct ast_node
{
    enum node_type type;
    union ast_data data;
};

// General purpose functions
/**
 * @brief Frees a 'ast_node' node
 *
 * Calls the appropriate function that will free the right type of node
 *
 * @param node Node to be freed
 */
void free_node(struct ast_node *node);
/**
 * @brief Executes a 'ast_node' node
 *
 * Calls the appropriate function that will execute the right type of node
 *
 * @param node Node to be executed
 * @return int Return status of the execution
 */
int exec_node(struct ast_node *node);

// Command node functions
/**
 * @brief Allocates a new 'NODE_COMMAND' type node
 *
 * Creates a new 'NODE_COMMAND' type node, and fills the 'args' member of the
 * struct with the 'args' argument of the function
 *
 * @param args Args of the commands to execute
 * @return struct ast_node* New node allocated
 */
struct ast_node *new_command_node(char **args);
/**
 * @brief Frees a 'NODE_COMMAND' type node, allocated by 'new_command_node'
 *
 * DON'T CALL IT DIRECTLY. It is normally called by 'free_node'
 *
 * @param node Node to be freed
 */
void free_command_node(struct ast_node *node);
/**
 * @brief Executes a 'NODE_COMMAND' type node
 *
 * If the first argument is the name of a builtin, executes the builtin. Else,
 * try to execute the command by creating a new process and using execvp. DO NOT
 * CALL DIRECTLY.
 *
 * @param node Node to be executed
 * @return int Return status of the execution
 */
int exec_command_node(struct ast_node *node);

// List node functions
/**
 * @brief Allocates a new 'NODE_LIST' type node
 *
 * Creates a new 'NODE_LIST' type node, with an empty node list.
 *
 * @return struct ast_node* struct ast_node* New node allocated
 */
struct ast_node *new_list_node();
/**
 * @brief Push a node to the AST list node
 *
 * Push the node 'added' to the list node 'node', updating the node length and
 * reallocating if needed
 *
 * @param node Node to be pushed into
 * @param added Node to be added to the list vector
 */
void list_node_push(struct ast_node *node, struct ast_node *added);
/**
 * @brief Frees a 'NODE_LIST' type node, allocated by 'new_list_node'
 *
 * DON'T CALL IT DIRECTLY. It is normally called by 'free_node'
 *
 * @param node Node to be freed
 */
void free_list_node(struct ast_node *node);
/**
 * @brief Executes a 'NODE_LIST' type node
 *
 * Executes the node in the list vector in succession.
 *
 * @param node List node to be executed
 * @return int Return status of the last node executed
 */
int exec_list_node(struct ast_node *node);

// If node functions
/**
 * @brief Allocates a new 'NODE_LIST' type node
 *
 * Creates a new empty 'NODE_IF'
 *
 * @return struct ast_node* Node to be allocated
 */
struct ast_node *new_if_node();
/**
 * @brief Frees a 'NODE_IF' type node, allocated by 'new_if_node'
 *
 * DON'T CALL IT DIRECTLY. It is normally called by 'free_node'
 *
 * @param node Node to be freed
 */
void free_if_node(struct ast_node *node);
/**
 * @brief Executes a 'NODE_IF' type node
 *
 * See the structure documentation for the execution. DON'T CALL DIRECTLY.
 *
 * @param node Node to be executed
 * @return int Return status of the if structure
 */
int exec_if_node(struct ast_node *node);

// Redirections related functions
/**
 * @brief Allocates a new redirection structure
 *
 * Replaced needs to be a valid file descriptor number. The source can be a file
 * descriptor number, the name of a file, or a '-' to close the replaced file
 * descriptor
 *
 * @param source Source redirection (file or file descriptor or '-')
 * @param replaced Replaced file descriptor
 * @param type Type of redirection ('<' or '>' or '>>' or ... )
 * @return struct redirection* Allocated redirection
 */
struct redirection *new_redirection(char *source, char *replaced,
                                    enum token_type type);
/**
 * @brief Frees a redirection allocated by 'new_redirection'
 *
 * Frees the structure and closes the extra file descriptor opened. Does not
 * perform the undoing of the redirection
 *
 * @param r Redirection to be freed
 */
void free_redirection(struct redirection *r);
/**
 * @brief Executes the redirection
 *
 * See documentation page for the redirection structure for more details.
 *
 * @param r Redirection to be executed
 * @return int Error status of the redirection execution
 */
int execute_redirection(struct redirection *r);
/**
 * @brief Undo a redirection
 *
 * See documentation page for the redirection structure for more details.
 *
 * @param r Redirection to undo
 * @return int Error status of the redirection undoing
 */
int undo_redirection(struct redirection *r);

/**
 * @brief Allocates a new 'NODE_REDIRECT_LIST' type node
 *
 * Creates a new empty 'NODE_REDIRECT_LIST' type node
 *
 * @return struct ast_node* Allocated node
 */
struct ast_node *new_redirec_list_node();
/**
 * @brief Frees a 'NODE_REDIREC_LIST' type node allocated by
 * 'new_redirec_list_node'
 *
 * DON"T CALL IT DIRECTLY. It will be called by free_node
 *
 * @param node Node to be freed
 */
void free_redirec_list_node(struct ast_node *node);
/**
 * @brief Push a redirection structure to a redirection list vector
 *
 * Add a redirection to the list of a 'NODE_REDIRECTION_LIST' type node, and
 * handles the memory management
 *
 * @param node Node to be pushed into
 * @param add Redirection to be added
 */
void push_redirec_list_node(struct ast_node *node, struct redirection *add);
/**
 * @brief Execute a 'NODE_REDIREC_LIST' type node
 *
 * Executes the redirections contained in the struct's vector, executes the
 * 'child' node, and undo the redirections in reverse order.
 *
 * @param node Node to be executed
 * @return int Return status of the child node
 */
int exec_redirec_list_node(struct ast_node *node);

// While loop functions
/**
 * @brief Allocates a new 'NODE_WHILE' type node
 *
 * Creates a new empty 'NODE_WHILE' type node
 *
 * @return struct ast_node* Allocated node
 */
struct ast_node *new_while_node();
/**
 * @brief Frees a 'NODE_WHILE' type node allocated by 'new_while_node'
 *
 * DON"T CALL IT DIRECTLY. It will be called by free_node
 *
 * @param node Node to be freed
 */
void free_while_node(struct ast_node *node);
/**
 * @brief Execute a 'NODE_WHILE' type node
 *
 * See the documentation page for the AST node while for more information on the
 * node execution.
 *
 * @param node Node to be executed
 * @return int Return status of the last node executed
 */
int exec_while_node(struct ast_node *node);

// Until loop functions
/**
 * @brief Allocates a new 'NODE_UNTIL' type node
 *
 * Creates a new empty 'NODE_UNTIL' type node
 *
 * @return struct ast_node* Allocated node
 */
struct ast_node *new_until_node();
/**
 * @brief Frees a 'NODE_UNTIL' type node allocated by 'new_until_node'
 *
 * DON"T CALL IT DIRECTLY. It will be called by free_node
 *
 * @param node Node to be freed
 */
void free_until_node(struct ast_node *node);
/**
 * @brief Execute a 'NODE_UNTIL' type node
 *
 * See the documentation page for the AST node until for more information on the
 * node execution.
 *
 * @param node Node to be executed
 * @return int Return status of the last node executed
 */
int exec_until_node(struct ast_node *node);

// Pipe functions
/**
 * @brief Allocates a new 'NODE_PIPE' type node
 *
 * Creates a new empty 'NODE_PIPE' type node
 *
 * @return struct ast_node* Allocated node
 */
struct ast_node *new_pipe_node();
/**
 * @brief Frees a 'NODE_PIPE' type node allocated by 'new_pipe_node'
 *
 * DON"T CALL IT DIRECTLY. It will be called by free_node
 *
 * @param node Node to be freed
 */
void free_pipe_node(struct ast_node *node);
/**
 * @brief Execute a 'NODE_PIPE' type node
 *
 * See the documentation page for the AST node pipe for more information on the
 * node execution.
 *
 * @param node Node to be executed
 * @return int Return status of the last node, negated if needed
 */
int exec_pipe_node(struct ast_node *node);

// And/or functions
/**
 * @brief Allocates a new 'NODE_AND_OR' type node
 *
 * Creates a new empty 'NODE_AND_OR' type node
 *
 * @return struct ast_node* Allocated node
 */
struct ast_node *new_and_or_node();
/**
 * @brief Frees a 'NODE_AND_OR' type node allocated by 'new_and_or_node'
 *
 * DON"T CALL IT DIRECTLY. It will be called by free_node
 *
 * @param node Node to be freed
 */
void free_and_or_node(struct ast_node *node);
/**
 * @brief Execute a 'NODE_AND_OR' type node
 *
 * See the documentation page for the AST node pipe for more information on the
 * node execution.
 *
 * @param node Node to be executed
 * @return int Return status of the last node
 */
int exec_and_or_node(struct ast_node *node);

// Built-ins
/**
 * @brief Echo built-in
 *
 * Expects a 'NODE_COMMAND' type node. Prints its arguments to stdout, separated
 * by a space. The '-e' option unescapes characters like '\n'. The '-n' option
 * stops echo from printing a new line at the last argument
 *
 * @param node Command node that corresponds to the echo command
 * @return int Return status of echo
 */
int echo(struct ast_node *node);

int cd(struct ast_node *node);

// Utility functions
/**
 * @brief Simple utility function that checks if a character is a digit
 *
 * @param c Character to check
 * @return int Returns a non 0 value if character is a digit, 0 instead
 */
int is_digit(char c);
