#include "exec.h"
#include "utils.h"

struct ast_node *new_list_node()
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_LIST;
    ret->data.ast_list.capacity = 10;
    ret->data.ast_list.len = 0;
    ret->data.ast_list.nodes =
        xcalloc(ret->data.ast_list.capacity, sizeof(struct ast_node *));

    return ret;
}

void list_node_push(struct ast_node *node, struct ast_node *added)
{
    if (node->type != NODE_LIST)
    {
        fprintf(stderr, "trying to push node to non list node");
        return;
    }

    if (node->data.ast_list.len == node->data.ast_list.capacity)
    {
        node->data.ast_list.capacity *= 2;
        node->data.ast_list.nodes =
            xrealloc(node->data.ast_list.nodes,
                     sizeof(struct ast_node *) * node->data.ast_list.capacity);
    }
    node->data.ast_list.nodes[node->data.ast_list.len] = added;
    node->data.ast_list.len++;
}

void free_list_node(struct ast_node *node)
{
    if (node->type != NODE_LIST)
    {
        fprintf(stderr, "trying to free non list node");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_list.nodes != NULL)
        {
            for (size_t i = 0; i < node->data.ast_list.len; ++i)
            {
                if (node->data.ast_list.nodes[i] != NULL)
                    free_node(node->data.ast_list.nodes[i]);
            }
            free(node->data.ast_list.nodes);
        }
        free(node);
    }
}

int exec_list_node(struct ast_node *node)
{
    if (node->type != NODE_LIST)
    {
        fprintf(stderr, "trying to execute non list node");
        return -1;
    }

    int status = 0;

    if (node->data.ast_list.nodes != NULL)
    {
        for (size_t i = 0; i < node->data.ast_list.len; ++i)
        {
            status = exec_node(node->data.ast_list.nodes[i]);
            node->data.ast_list.nodes[i] = NULL;
        }
    }
    return status;
}