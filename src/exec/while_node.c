#include "exec.h"
#include "utils.h"

struct ast_node *new_while_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_WHILE;
    ret->data.ast_while.condition = NULL;
    ret->data.ast_while.body_list = NULL;

    return ret;
}

void free_while_node(struct ast_node *node)
{
    if (node->type != NODE_WHILE)
    {
        fprintf(stderr, "trying to free non while node\n");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_while.condition != NULL)
            free_node(node->data.ast_while.condition);
        if (node->data.ast_while.body_list != NULL)
            free_node(node->data.ast_while.body_list);
        free(node);
    }
}
int exec_while_node(struct ast_node *node)
{
    if (node->type != NODE_WHILE)
    {
        fprintf(stderr, "trying to execute non while node\n");
        return -1;
    }

    if (node->data.ast_while.condition == NULL)
    {
        fprintf(stderr, "missing condition node [while]\n");
        return -1;
    }

    if (node->data.ast_while.body_list == NULL)
    {
        fprintf(stderr, "missing body node [while]\n");
        return -1;
    }

    int cond = exec_node(node->data.ast_while.condition);
    int return_status = 0;
    while (cond == 0)
    {
        return_status = exec_node(node->data.ast_while.body_list);
        cond = exec_node(node->data.ast_while.condition);
    }

    return return_status;
}
