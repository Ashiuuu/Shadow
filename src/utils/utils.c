#include "utils.h"

inline void *xmalloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL)
    {
        fprintf(stderr, "malloc fail");
        abort();
    }

    return ret;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *ret = calloc(nmemb, size);
    if (ret == NULL)
    {
        fprintf(stderr, "calloc fail");
        abort();
    }

    return ret;
}

inline void *xrealloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);
    if (ret == NULL)
    {
        fprintf(stderr, "realloc fail");
        abort();
    }

    return ret;
}

size_t array_len(char **arr)
{
    if (arr == NULL)
    {
        return 0;
    }

    size_t ret = 0;
    while (arr[ret] != NULL)
        ret++;

    return ret;
}

void write_file(char *content)
{
    int fd = open("tree.dot", O_CREAT | O_APPEND | O_RDWR, 0777);                        
    write(fd, content, strlen(content));
    close(fd);
}