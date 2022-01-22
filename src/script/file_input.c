#include "file_input.h"
#include "variables.h"
#include "lexer.h"

void file_input(char **cmd_file)
{
    init_positional_arguments(cmd_file);

    struct lexer *lexer = lexer_new(input_from_file(cmd_file[0]));
    if (lexer == NULL)
    {
        if(variables != NULL)
            free_linked_list(variables);
        fprintf(stderr, "Unable to open %s\n", cmd_file[0]);
        variable_push_int("?", 127);
        return;
    }

    struct token *tok = lexer_peek(lexer);
    int return_status = 0;

    while (tok->type != TOKEN_EOF)
    {
        struct ast_node *ast = NULL;
        enum parser_status stat = parse_input(&ast, lexer);
        
        if (stat == PARSER_ERROR)
        {
            free_node(ast);
            variable_push_int("?", 2);
            lexer_free(lexer);
            return;
        }

        if (ast == NULL)
            continue;
        return_status = exec_node(ast);
        free_node(ast);

        tok = lexer_peek(lexer);
    }

    variable_push_int("?", return_status);
    lexer_free(lexer);
}

/*void file_input(char **cmd_file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fd = fopen(cmd_file[0], "r");
    if (fd == NULL)
    {
        if(variables)
            free_linked_list(variables);
        printf("Unable to open %s\n", cmd_file[0]);
        push_linked_list(variables, "?", "127");
        return;
    }

    init_positional_arguments(cmd_file);

    while ((read = getline(&line, &len, fd)) != -1)
    {
        if (line[0] == '#' || strcmp(line, "\n") == 0)
            continue;
        struct ast_node *ast = NULL;
        enum parser_status stat =
            parse_input(&ast, lexer_new(input_from_string(line)));
        if (stat == PARSER_ERROR)
        { // we had an error, but juste parse next command
            free_node(ast);
            continue;
        }
        if (ast == NULL)
        {
            continue;
        }
        char *exec_stat = xmalloc(sizeof(char) * 4);
        sprintf(exec_stat, "%d", exec_node(ast));
        push_linked_list(variables, "?", exec_stat);
        free(exec_stat);
        free_node(ast);
    }
    fclose(fd);
    if (line)
        free(line);
}*/
