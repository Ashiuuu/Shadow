#include "printer.h"

// Write ast into .dot file to create tree on pdf
void print_ast(struct ast_node *node)
{
    write_file(" -- ");
    if (node == NULL)
        return;
    if (node->type == NODE_COMMAND)
    {
        print_ast_command(node->data.ast_command);
    }
    else if (node->type == NODE_LIST)
    {
        for (size_t i = 0; i < node->data.ast_list.len; i++)
        {
            if (node->data.ast_list.nodes[i]->type == NODE_COMMAND)
            {
                print_ast_command(node->data.ast_list.nodes[i]->data.ast_command);
            }
            else if (node->data.ast_list.nodes[i]->type == NODE_IF)
            {
                print_ast_if(node->data.ast_list.nodes[i]->data.ast_if);
            }
            else
            {
                printf("Error printer.c type not found l.26\n");
            }
        }
    }
    else if (node->type == NODE_IF)
    {
        return;
    }
    else
    {
        return;
    }
}

// Print command node
void print_ast_command(struct ast_node_command ast_command)
{
    if (array_len(ast_command.args) == 1)
    {
        write_file("\"");
        write_file(ast_command.args[0]);
        write_file("\";\n");
    }
    for (size_t i = 0; i < array_len(ast_command.args); i++)
    {
        if (i % 2 == 0)
        {
            write_file(ast_command.args[i]);
            write_file(" -- ");
        }
        else
        {
            write_file(ast_command.args[i]);
            write_file(";\n");
        }
    }
}

// Print if node
void print_ast_if(struct ast_node_if ast_if)
{
    write_file("if");
    // Condition
    print_ast(ast_if.condition);
    // Body list
    print_ast(ast_if.body_list);
    // elif
    print_ast(ast_if.elif);
    
    write_file("fi;\n");
}