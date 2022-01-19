#include "exec.h"
#include "utils.h"

struct ast_node *new_and_or_node(enum token_type type)
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_AND_OR;
    ret->data.ast_and_or.left = NULL;
    ret->data.ast_and_or.right = NULL;
    ret->data.ast_and_or.type = type;

    return ret;
}

void free_and_or_node(struct ast_node *node)
{
    if (node->type != NODE_AND_OR)
    {
        fprintf(stderr, "trying to free non and or node\n");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_and_or.left != NULL)
            free_node(node->data.ast_and_or.left);
        if (node->data.ast_and_or.right != NULL)
            free_node(node->data.ast_and_or.right);
        free(node);
    }
}

int exec_and_or_node(struct ast_node *node)
{
    if (node->type != NODE_AND_OR)
    {
        fprintf(stderr, "trying to execute non and or node\n");
        return -1;
    }

    if (node->data.ast_and_or.left == NULL
        || node->data.ast_and_or.right == NULL)
    {
        fprintf(stderr, "and_or node missing left or right operand\n");
        return -1;
    }

    // both command must echo bar
    // false && echo foo || echo bar
    // true || echo foo && echo bar
    int status = exec_node(node->data.ast_and_or.left);
    if (node->data.ast_and_or.type == TOKEN_AND && status == 0)
        status = exec_node(node->data.ast_and_or.right);
    else if (node->data.ast_and_or.type == TOKEN_OR && status != 0)
        status = exec_node(node->data.ast_and_or.right);

    return status;
}