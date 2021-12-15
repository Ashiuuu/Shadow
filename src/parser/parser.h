#pragma once

#include <stdio.h>

enum parser_status
{
    PARSER_OK,
    PARSER_ERROR
};

enum parser_status parse_input(FILE *input);
