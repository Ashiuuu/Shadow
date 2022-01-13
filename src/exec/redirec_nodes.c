#include "exec.h"
#include "utils.h"

struct redirection *new_redirection()
{
    struct redirection *ret = xmalloc(sizeof(struct redirection));
    ret->io_number = NULL;
    ret->dest = NULL;
    ret->type = TOKEN_ERROR;

    return ret;
}

struct ast_node *new_redirec_list_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_REDIREC_LIST;
    ret->data.ast_redirec_list.capacity = 5;
    ret->data.ast_redirec_list.len = 0;
    ret->data.ast_redirec_list.redirections = xmalloc(sizeof(struct redirection) * ret->data.ast_redirec_list.capacity);
    ret->data.ast_redirec_list.child = NULL;

    return ret;
}

void free_redirection(struct redirection *r)
{
    if (r != NULL)
    {
        if (r->io_number != NULL)
            free(r->io_number);
        if (r->dest != NULL)
            free(r->dest);
        free(r);
    }
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
        node->data.ast_redirec_list.redirections = xrealloc(sizeof(struct redirection) * node->data.ast_redirec_list.capacity);
    }

    node->data.ast_redirec_list.redirections[node->data.ast_redirec_list.len] = add;
    node->data.ast_redirec_list.len++;
}

int exec_redirec_list_node(struct ast_node *node)
{
    if (node->type != NODE_REDIREC_LIST)
    {
        fprintf(stderr, "trying to execute non redirection list node\n");
        free_node(node);
        return -1;
    }

    // execute redirections with dup2 (and backup)

    // redirection structures:
    // A: "2" >& "3"
    // B: "1" >& "2"
    // C: "3" >& "1"
    // 
    // A.copy = dup(3)
    // dup2(2, 3) // copy 2 into 3
    // ...
    /// dup2(copy, 2)

    // BEFORE: 1 stdout, 2 stderr, 3 custom
    // 2>&3 1>&2 3>&1
    // MIDDLE: 1 stderr, 2 stdout, 3 custom (stderr)
    // 1>&3 2>&1 3>&2
    // AFTER:  1 stdout, 2 stderr, 3 custom (stderr)

    // execute child node

    // restore backup

    // free node
}