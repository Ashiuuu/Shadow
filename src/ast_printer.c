#include <stdio.h>

#include "exec.h"
#include "parser.h"
#include "io.h"
#include "lexer.h"

void print_command_node(struct ast_node *node)
{
    if (node->type != NODE_COMMAND)
    {
        fprintf(stderr, "[*] trying to print non command node\n");
        return;
    }

    printf("Command node args:\n");
    for (size_t i = 0; node->data.ast_command.args[i] != NULL; ++i)
    {
        printf("  - %s\n", node->data.ast_command.args[i]);
    }
}

void print_list_node(struct ast_node *node)
{
    if (node->type != NODE_LIST)
    {
        fprintf(stderr, "[*] trying to print non list node\n");
        return;
    }

    printf("List of nodes:\n");
    for (size_t i = 0; i < node->data.ast_list.len; ++i)
    {
        print_command_node(node->data.ast_list.nodes[i]);
        printf("\n\n");
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s [COMMAND]", argv[0]);
        return -1;
    }

    struct INPUT *input = input_from_string(argv[1]);
    struct lexer *lexer = lexer_new(input);
    struct ast_node *ast = NULL;
    parse_input(&ast, lexer);
    if (ast->type == NODE_LIST)
    {
        printf("\n");
        printf("%ld (/%ld)\n", ast->data.ast_list.len, ast->data.ast_list.capacity);
        print_list_node(ast);
    }
    // print ast

    return 0;
}