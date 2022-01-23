#include <string.h>

#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include "variables.h"

int is_special(char c)
{
    return c == '@' || c == '*' || c == '?' || c == '$'
        || (c >= '0' && c <= '9') || c == '#';
}

char *variable_search_and_replace(char *string)
{
    // search for $ and call appropriate variable recognition function
    if (string == NULL)
        return NULL;

    size_t len = strlen(string);

    for (size_t i = 0; i < len; ++i)
    {
        char *name;
        if (string[i] == '$')
        {
            if (i + 1 < len)
            {
                if (string[i + 1] == '{')
                {
                    name =
                        parse_variable_bracket(string + i + 2); // skip bracket
                    size_t name_len = strlen(name) + 2; // { and }
                    char *value = get_variable(name);
                    size_t val_len = 0;
                    if (value != NULL)
                        val_len = strlen(value);
                    char *first_half = strndup(string, i);
                    first_half = xrealloc(
                        first_half, sizeof(char) * (len + val_len - name_len));
                    if (value != NULL)
                        first_half = strcat(first_half, value);
                    first_half =
                        strcat(first_half, (string + i + name_len + 1));
                    free(string);
                    free(name);
                    return first_half;
                }
                else if (is_special(string[i + 1]))
                {
                    name = parse_special(string + i + 1);
                    size_t name_len = strlen(name);
                    char *value = get_variable(name);
                    size_t val_len = 0;
                    if (value != NULL)
                        val_len = strlen(value);
                    char *first_half = strndup(string, i);
                    first_half = xrealloc(
                        first_half, sizeof(char) * (len + val_len - name_len));
                    if (value != NULL)
                        first_half = strcat(first_half, value);
                    first_half =
                        strcat(first_half, (string + i + name_len + 1));
                    free(string);
                    free(name);
                    return first_half;
                }
                else if (is_alpha(string[i + 1]))
                {
                    name = parse_alpha(string + i + 1);
                    size_t name_len = strlen(name);
                    char *value = get_variable(name);
                    size_t val_len = 0;
                    if (value != NULL)
                        val_len = strlen(value);
                    char *first_half = strndup(string, i);
                    first_half = xrealloc(
                        first_half, sizeof(char) * (len + val_len - name_len));
                    if (value != NULL)
                        first_half = strcat(first_half, value);
                    first_half =
                        strcat(first_half, (string + i + name_len + 1));
                    free(string);
                    free(name);
                    return first_half;
                }
                else
                    continue;
            }
        }
    }
    return string;
}

char *parse_variable_bracket(char *string)
{
    size_t capacity = 5;
    size_t len = 0;
    char *ret = xmalloc(sizeof(char) * capacity);

    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        char c = string[i];
        if (c != '}')
        {
            if (len == capacity)
            {
                capacity *= 2;
                ret = xrealloc(ret, sizeof(char) * capacity);
            }
            ret[len] = c;
            len++;
        }
    }
    capacity = len + 1;
    ret = xrealloc(ret, sizeof(char) * capacity);
    ret[len] = '\0';
    return ret;
}

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
