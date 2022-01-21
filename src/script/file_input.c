#include "file_input.h"
#include "variables.h"

void file_input(char **cmd_file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int return_status = 0;
    FILE *fd = fopen(cmd_file[0], "r");
    if (fd == NULL)
    {
        if(variables)
            free_linked_list(variables);
        printf("Unable to open %s\n", cmd_file[0]);
        push_linked_list(variables, "?", -1);
        return;
    }

    init_positial_arguments(cmd_file);

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
        push_linked_list(variables, "?", exec_node(ast));
        free_node(ast);
    }
    fclose(fd);
    if (line)
        free(line);
}
