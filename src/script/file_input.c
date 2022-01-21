#include "file_input.h"

int file_input(char *cmd_file)
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int return_status = 0;
    FILE * fd = fopen(cmd_file, "r");
    if (fd == NULL)
    {
        printf("Unable to open %s\n", cmd_file);
        return -1;
    }

    while ((read = getline(&line, &len, fd)) != -1)
    {
        if (line[0] == '#' || strcmp(line, "\n") == 0)
            continue;
        struct ast_node *ast = NULL;
        enum parser_status stat = parse_input(&ast, lexer_new(input_from_string(line)));
        if (stat == PARSER_ERROR)
        { // we had an error, but juste parse next command
            free_node(ast);
            continue;
        }
        if (ast == NULL)
        {
            continue;
        }
        return_status = exec_node(ast);
        free_node(ast);

    }
    fclose(fd);
    if (line)
        free(line);
    return return_status;
}