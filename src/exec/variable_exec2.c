#include <string.h>

#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include "variables.h"

char *parse_special(char *string)
{
    char c = *string;
    char *ret;

    if (c <= '9' && c >= '0')
    {
        size_t capacity = 5;
        size_t len = 0;
        ret = xmalloc(sizeof(char) * capacity);

        while (c >= '0' && c <= '9')
        {
            if (len == capacity)
            {
                capacity *= 2;
                ret = xrealloc(ret, sizeof(char) * capacity);
            }
            ret[len] = c;
            len++;
            c = *(string + len);
        }

        capacity = len + 1;
        ret = xrealloc(ret, sizeof(char) * capacity);
        ret[len] = '\0';
    }
    else
    {
        ret = xmalloc(sizeof(char) * 2);
        ret[0] = c;
        ret[1] = '\0';
    }

    return ret;
}

char *parse_alpha(char *string)
{
    // parse into string until non alphanum or _ is detected
    size_t len = 0;
    size_t capacity = 10;
    char *ret = xmalloc(sizeof(char) * capacity);

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        char c = string[i];
        if (is_alphanum(c) || c == '_')
        {
            if (len == capacity)
            {
                capacity *= 2;
                ret = xrealloc(ret, sizeof(char) * capacity);
            }
            ret[len] = c;
            len++;
        }
        else // not a variable character, stop parsing
        {
            break;
        }
    }

    capacity = len + 1;
    ret = xrealloc(ret, sizeof(char) * capacity);
    ret[len] = '\0';
    return ret;
}
