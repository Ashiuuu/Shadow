#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "exec.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

int file_input(char *cmd_file);