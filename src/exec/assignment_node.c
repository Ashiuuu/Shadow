#include "exec.h"
#include "utils.h"
#include "variables.h"

struct ast_node *new_assignment_node(char *string)
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_ASSIGNMENT;
    ret->data.ast_assignment.string = strdup(string);
    ret->data.ast_assignment.tok = NULL;

    return ret;
}

void free_assignment_node(struct ast_node *node)
{
    if (node->type != NODE_ASSIGNMENT)
    {
        fprintf(stderr, "trying to free non assignment node\n");
        return;
    }

    if (node != NULL)
    {
        if (node->data.ast_assignment.string != NULL)
        {
            free(node->data.ast_assignment.string);
            node->data.ast_assignment.string = NULL;
        }
        if (node->data.ast_assignment.tok != NULL)
        {
            token_free(node->data.ast_assignment.tok);
            node->data.ast_assignment.tok = NULL;
        }
        free(node);
    }
}

int exec_assignment_node(struct ast_node *node)
{
    char *val = NULL;
    if (node->data.ast_assignment.tok->type == TOKEN_EXPAND)
    {
        val = variable_search_and_replace(node->data.ast_assignment.tok->value);
        node->data.ast_assignment.tok->value = val;
    }
    else
        val = node->data.ast_assignment.tok->value;
    push_linked_list(variables, node->data.ast_assignment.string, val);
    return 0;

    return 0;
}
