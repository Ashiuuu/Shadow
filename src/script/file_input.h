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

/**
 * @brief file input function
 *
 * This function opens a file entered as a parameter and reads it to execute
 * functions.
 *
 * @param cmd_file
 * @return int
 */
int file_input(char *cmd_file);