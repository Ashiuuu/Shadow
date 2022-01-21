#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief INPUt structure
 * 
 */
struct INPUT
{
    ///current character to stream
    char current_char;
    ///next character to stream
    char next_char;
    ///a stream
    FILE *stream;
};

/**
 * @brief Allocate and create a structure INPUT
 * 
 * @param stream 
 * @return struct INPUT* 
 */
struct INPUT *new_input(FILE *stream);

/**
 * @brief Collect a string and create a INPUT structure
 * 
 * @param s 
 * @return struct INPUT* 
 */
struct INPUT *input_from_string(char *s);

/**
 * @brief Collect a string to stdin to create a INPUT structure
 * 
 * @return struct INPUT* 
 */
struct INPUT *input_from_stdin();

/**
 * @brief Open a file with filename and return a struct INPUT
 * 
 * @param filename 
 * @return struct INPUT* 
 */
struct INPUT *input_from_file(char *filename);

/**
 * @brief pop a current on struct INPUT
 * 
 * @param input 
 * @return char 
 */
char pop_char(struct INPUT *input);

/**
 * @brief Free input structure
 * 
 * @param input 
 */
void free_input(struct INPUT *input);

/**
 * @brief Convert a string to a stream
 * 
 * @param buffer 
 * @return FILE* 
 */
FILE *string_to_stream(char *buffer);

/**
 * @brief Open file with filename
 * 
 * @param filename 
 * @return FILE* 
 */
FILE *open_file(char *filename);
