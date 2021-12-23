#pragma once

#include <stdlib.h>
#include <stdio.h>

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);
size_t array_len(char **arr);
