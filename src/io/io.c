#include "io.h"

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
