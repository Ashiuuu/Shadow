#include "exec.h"
#include "utils.h"

struct ast_node *new_until_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_UNTIL;
    ret->data.ast_until.condition = NULL;
    ret->data.ast_until.body_list = NULL;

    return ret;
}

void free_until_node(struct ast_node *node)
{
    if (node->type != NODE_UNTIL)
    {
        fprintf(stderr, "trying to free non until node\n");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_until.condition != NULL)
            free_node(node->data.ast_until.condition);
        if (node->data.ast_until.body_list != NULL)
            free_node(node->data.ast_until.body_list);
        free(node);
    }
}

int exec_until_node(struct ast_node *node)
{
    if (node->type != NODE_UNTIL)
    {
        fprintf(stderr, "trying to execute non until node\n");
        return -1;
    }

    if (node->data.ast_until.condition == NULL)
    {
        fprintf(stderr, "missing condition node [until]\n");
        return -1;
    }

    if (node->data.ast_until.body_list == NULL)
    {
        fprintf(stderr, "missing body node [until]\n");
        return -1;
    }

    int cond = exec_node(node->data.ast_until.condition);
    int return_status = 0;
    while (cond != 0)
    {
        return_status = exec_node(node->data.ast_until.body_list);
        cond = exec_node(node->data.ast_until.condition);
    }

    return return_status;
}
