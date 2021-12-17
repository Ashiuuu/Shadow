#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct INPUT
{
    char current_char;
    char next_char;
    FILE *stream;
};

struct INPUT *new_input(FILE *stream);
struct INPUT *input_from_string(char *s);
struct INPUT *input_from_stdin();
struct INPUT *input_from_file(char *filename);
char pop_char(struct INPUT *input);


FILE *string_to_stream(char *buffer);
FILE *open_file(char *filename);
