#include "io.h"

struct INPUT *new_input(FILE *stream)
{
    struct INPUT *ret = malloc(sizeof(struct INPUT));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to malloc INPUT struct");
        abort();
    }
    ret->stream = stream;
    ret->current_char = fgetc(stream);
    if (ret->current_char == EOF)
        ret->next_char = EOF;
    else
        ret->next_char = fgetc(stream);

    return ret;
}

struct INPUT *input_from_string(char *s)
{
    FILE *stream = string_to_stream(s);
    if (stream == NULL)
        return NULL;
    return new_input(stream);
}

struct INPUT *input_from_stdin()
{
    return new_input(stdin);
}

struct INPUT *input_from_file(char *filename)
{
    FILE *stream = open_file(filename);
    return new_input(stream);
}

char pop_char(struct INPUT *input)
{
    if (input->next_char == EOF)
    {
        input->current_char = EOF;
        return input->current_char;
    }
    input->current_char = input->next_char;
    input->next_char = fgetc(input->stream);

    return input->current_char;
}

void free_input(struct INPUT *input)
{
    fclose(input->stream);
    free(input);
}

FILE *string_to_stream(char *buffer)
{
    FILE *stream = fmemopen(buffer, strlen(buffer), "r");
    if (stream == NULL)
    {
        fprintf(stderr, "Unable to open stream for buffer %s\n", buffer);
        abort();
    }

    return stream;
}

FILE *open_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
        abort();
    }

    return file;
}
