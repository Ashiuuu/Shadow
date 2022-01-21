#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "exec.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

int file_input(char *cmd_file);