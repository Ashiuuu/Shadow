#include <string.h>

#include "exec.h"
#include "utils.h"
#include "variables.h"
#include "lexer.h"

int is_special(char c)
{
    return c == '@' || c == '*' || c == '?' || c == '$' || (c >= '0' && c <= '9') || c == '#';
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
                    //name = parse_variable_bracket(string + i + 2); 
                    //char *value = search_variable(name);
                    //replace_variable_in_string(string[i], value);
                }
                else if (is_special(string[i + 1]))
                {
                    name = parse_special(string + i + 1);
                    size_t name_len = strlen(name);
                    char *value = get_linked_list(variables, name);
                    size_t val_len = 0;
                    if (value != NULL)
                        val_len = strlen(value);
                    char *first_half = strndup(string, i);
                    first_half = xrealloc(first_half, sizeof(char) * (len + val_len - name_len));
                    if (value != NULL)
                        first_half = strcat(first_half, value);
                    first_half = strcat(first_half, (string + i + name_len + 1));
                    free(string);
                    free(name);
                    return first_half;
                }
                else if (is_alpha(string[i + 1]))
                    continue;
                else
                    continue;
            }
        }
    }
    return NULL;
}

char *parse_variable_bracket(char *string)
{
    string = string;
    return NULL;
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
