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