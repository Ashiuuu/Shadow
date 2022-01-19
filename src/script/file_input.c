#include "file_input.h"

void file_input(char *cmd_file)
{
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE * fd = fopen(cmd_file, "r");
    if (fd == NULL)
    {
        printf("Unable to open %s\n", cmd_file);
        return;
    }

    while ((read = getline(&line, &len, fd)) != -1)
    {
        if (line[0] == '#' || strcmp(line, "\n") == 0)
            continue;
        struct ast_node *ast = NULL;
        parse_input(&ast, lexer_new(input_from_string(line)));
        exec_node(ast);
        free_node(ast);
    }
    fclose(fd);
    if (line)
        free(line);
}