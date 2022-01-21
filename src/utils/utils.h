#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief xmalloc function
 *
 * This function mallocs a pointer and checks if it is properly allocated.
 *
 * @param size
 * @return void*
 */
void *xmalloc(size_t size);

/**
 * @brief xcalloc function
 *
 * This function mallocs a pointer and checks if it is properly allocated.
 *
 * @param nmemb
 * @param size
 * @return void*
 */
void *xcalloc(size_t nmemb, size_t size);

/**
 * @brief xrealloc function
 *
 * This function mallocs a pointer and checks if it is properly allocated.
 *
 * @param ptr
 * @param size
 * @return void*
 */
void *xrealloc(void *ptr, size_t size);

/**
 * @brief array len function
 *
 * This function measures the size of an array.
 *
 * @param arr
 * @return size_t
 */
size_t array_len(char **arr);

/**
 * @brief write file function
 *
 * This function opens a file to name tree.dot to write inside, this file is
 * used to display an ast in visual form.
 *
 * @param content
 */
void write_file(char *content);
