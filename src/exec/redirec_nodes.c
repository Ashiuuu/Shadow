#include "exec.h"
#include "tokens.h"
#include "utils.h"

int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

struct ast_node *new_redirec_list_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_REDIREC_LIST;
    ret->data.ast_redirec_list.capacity = 5;
    ret->data.ast_redirec_list.len = 0;
    ret->data.ast_redirec_list.redirections = xmalloc(
        sizeof(struct redirection) * ret->data.ast_redirec_list.capacity);
    ret->data.ast_redirec_list.child = NULL;

    return ret;
}

void free_redirec_list_node(struct ast_node *node)
{
    if (node == NULL)
        return;

    if (node->type != NODE_REDIREC_LIST)
    {
        fprintf(stderr, "trying to free non redirection list node\n");
        return;
    }

    if (node->data.ast_redirec_list.redirections != NULL)
    {
        for (size_t i = 0; i < node->data.ast_redirec_list.len; ++i)
            free_redirection(node->data.ast_redirec_list.redirections[i]);
        free(node->data.ast_redirec_list.redirections);
    }
    if (node->data.ast_redirec_list.child != NULL)
        free_node(node->data.ast_redirec_list.child);
    free(node);
}

void push_redirec_list_node(struct ast_node *node, struct redirection *add)
{
    if (node->type != NODE_REDIREC_LIST)
    {
        fprintf(stderr, "trying to push to non redirection list node\n");
        return;
    }

    if (node->data.ast_redirec_list.len == node->data.ast_redirec_list.capacity)
    {
        node->data.ast_redirec_list.capacity *= 2;
        node->data.ast_redirec_list.redirections = xrealloc(
            node->data.ast_redirec_list.redirections,
            sizeof(struct redirection) * node->data.ast_redirec_list.capacity);
    }

    node->data.ast_redirec_list.redirections[node->data.ast_redirec_list.len] =
        add;
    node->data.ast_redirec_list.len++;
}

int exec_redirec_list_node(struct ast_node *node)
{
    if (node->type != NODE_REDIREC_LIST)
    {
        fprintf(stderr, "trying to execute non redirection list node\n");
        return -1;
    }

    // execute redirections

    for (size_t i = 0; i < node->data.ast_redirec_list.len; ++i)
    {
        int stat =
            execute_redirection(node->data.ast_redirec_list.redirections[i]);
        if (stat == -1)
        {
            fprintf(stderr,
                    "a redirection failed, stoping execution of redirection "
                    "list\n");
            return -1;
        }
    }

    // execute child node

    int return_status = exec_node(node->data.ast_redirec_list.child);

    fflush(stdout);
    fflush(stderr);

    // restore backup

    if (node->data.ast_redirec_list.len == 0)
    {
        return return_status;
    }

    for (size_t i = node->data.ast_redirec_list.len - 1; i > 0; --i)
    {
        if (node->data.ast_redirec_list.redirections[i] == NULL)
            continue;
        int stat =
            undo_redirection(node->data.ast_redirec_list.redirections[i]);
        if (stat == -1)
        {
            fprintf(stderr,
                    "undoing a redirection failed, stoping execution of "
                    "redirection list\n");
            return -1;
        }
    }

    // free node
    return return_status;
}
