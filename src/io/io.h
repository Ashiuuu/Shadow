#pragma once

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *string_to_stream(char *buffer);
FILE *open_file(char *filename);
