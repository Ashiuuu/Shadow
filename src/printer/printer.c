#include "printer.h"

// Write ast into .dot file to create tree on pdf
void print_ast(struct ast_node *node, char *type)
{
    // write_file(" -- ");
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
            // printf("%ld\n", i);
            if (node->data.ast_list.nodes[i]->type == NODE_COMMAND)
            {
                print_ast_command(
                    node->data.ast_list.nodes[i]->data.ast_command);
            }
            else if (node->data.ast_list.nodes[i]->type == NODE_IF)
            {
                print_ast_if(node->data.ast_list.nodes[i]->data.ast_if, type);
            }
            else if (node->data.ast_list.nodes[i]->type == NODE_REDIREC_LIST)
            {
                print_ast_redir(
                    node->data.ast_list.nodes[i]->data.ast_redirec_list);
            }
            else
            {
                printf("%d\n", node->data.ast_list.nodes[i]->type);
                printf("Error printer.c type not found l.26\n");
            }
        }
    }
    else if (node->type == NODE_IF)
    {
        printf("oui\n");
        print_ast_if(node->data.ast_if, type);
        // write_file("\"");
        // write_file(node->data.ast_if.elif.data.ast_if);
        // write_file("\";\n");
    }
    else
    {
        printf("Not supported Node\n");
        printf("%d\n", node->type);
        return;
    }
}

// Print command node
void print_ast_command(struct ast_node_command ast_command)
{
    if (array_len(ast_command.args_strings) == 1)
    {
        write_file("\"");
        write_file(ast_command.args_strings[0]);
        write_file("\";\n");
    }
    write_file("\"");
    for (size_t i = 0; i < array_len(ast_command.args_strings); i++)
    {
        write_file(ast_command.args_strings[i]);
        if (i + 1 != array_len(ast_command.args_strings))
            write_file(" ");
    }
    write_file("\";\n");
}

// Print if node
void print_ast_if(struct ast_node_if ast_if, char *type)
{
    write_file("\"if\";\n");
    printf("%s\n", type);
    // Condition
    if (ast_if.condition)
    {
        if (strcmp(type, "if"))
        {
            write_file("\"if\" -- \"condition\";\n");
            write_file("\"condition\" -- ");
            print_ast(ast_if.condition, "if");
        }
        else
        {
            write_file("\"elif\" -- \"condition\";\n");
            write_file("\"condition\" -- ");
            print_ast(ast_if.condition, "elif");
        }
    }
    // Body list
    if (ast_if.body_list)
    {
        if (strcmp(type, "if"))
        {
            write_file("\"if\" -- \"body\";\n");
            write_file("\"body\" -- ");
            print_ast(ast_if.body_list, "if");
        }
        else
        {
            write_file("\"elif\" -- \"body\";\n");
            write_file("\"body\" -- ");
            print_ast(ast_if.body_list, "elif");
        }
    }
    // Elif
    if (ast_if.elif)
    {
        write_file("\"if\" -- \"elif\";\n");
        print_ast(ast_if.elif, "elif");
    }
    write_file("\"if\" -- \"fi\";\n");
}

void print_ast_redir(struct ast_node_redirec_list ast_redir)
{
    print_ast(ast_redir.child, "");
}
