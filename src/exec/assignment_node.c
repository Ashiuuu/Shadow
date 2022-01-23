#include "exec.h"
#include "utils.h"
#include "variables.h"

struct ast_node *new_assignment_node(char *string)
{
    struct ast_node *ret = xmalloc(sizeof(struct ast_node));
    ret->type = NODE_ASSIGNMENT;
    ret->data.ast_assignment.string = strdup(string);

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
            free(node->data.ast_assignment.string);
        free(node);
    }
}

int exec_assignment_node(struct ast_node *node)
{
    // split by the first '='

    for (size_t i = 0; node->data.ast_assignment.string[i] != '\0'; ++i)
    {
        char c = node->data.ast_assignment.string[i];
        if (c == '=')
        {
            char *n = strndup(node->data.ast_assignment.string, i);
            push_linked_list(variables, n, node->data.ast_assignment.string + i + 1);
            free(n);
            return 0;
        }
    }

    return 0;
}
