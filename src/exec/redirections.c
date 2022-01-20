#include "exec.h"
#include "utils.h"

int my_atoi(char *s)
{
    int ret = 0;

    for (size_t i = 0; s[i] != '\0'; ++i)
    {
        if (!is_digit(s[i]))
            return -1; // error, isn't a number
        ret = (10 * ret) + (s[i] - '0');
    }

    return ret;
}

struct redirection *new_redirection(char *source, char *replaced,
                                    enum token_type type)
{
    int s_fd;
    int rep_fd;

    if (source == NULL)
    {
        fprintf(stderr, "source file descriptor is NULL [new redirection]\n");
        return NULL;
    }

    if (type == TOKEN_FRED_IN || type == TOKEN_FDRED_IN || type == TOKEN_BIRED)
        rep_fd = STDIN_FILENO;
    else if (type == TOKEN_FRED_OUT || type == TOKEN_FDRED_OUT
             || type == TOKEN_FRED_APP || type == TOKEN_FRED_FORCE)
        rep_fd = STDOUT_FILENO;
    else
    {
        fprintf(stderr, "wrong token type [new redirection]\n");
        return NULL;
    }

    if (replaced != NULL)
    {
        int to_int = my_atoi(replaced);
        if (to_int == -1)
        {
            fprintf(stderr, "%s is not a number [new redirection]\n", replaced);
            return NULL;
        }
        rep_fd = to_int;
    }

    int src_int = my_atoi(source);
    if (src_int != -1)
    {
        s_fd = src_int;
    }
    else if (source[0] == '-' && strlen(source)) // source is only '-'
    {
        s_fd = -1; // means the rep_fd will be closed
    }
    else // neither a number or '-'
    {
        if (type == TOKEN_FDRED_IN || type == TOKEN_FDRED_OUT) // >& or <&
        {
            fprintf(stderr,
                    "must use valid file descriptor with >& or <&, not word "
                    "[new redirection]\n");
            return NULL;
        }
        int flags = O_CREAT;
        if (type == TOKEN_FRED_OUT || type == TOKEN_FDRED_OUT
            || type == TOKEN_FRED_APP || type == TOKEN_FRED_FORCE)
            flags |= O_WRONLY;
        else
            flags |= O_RDONLY;
        if (type == TOKEN_FRED_APP)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;

        s_fd = open(source, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (s_fd == -1)
        {
            fprintf(stderr, "opening file %s failed [new redirection]\n",
                    source);
            return NULL;
        }
    }

    struct redirection *ret = xmalloc(sizeof(struct redirection));
    ret->source_fd = s_fd;
    ret->replaced_fd = rep_fd;
    ret->duped_fd = -1;

    return ret;
}

int execute_redirection(struct redirection *r)
{
    // replaced 'replaced_fd' with 'source_fd' while keeping 'replaced_fd' in
    // 'duped_fd'
    if (r == NULL)
    {
        fprintf(stderr, "trying to execute NULL redirection\n");
        return -1;
    }

    r->duped_fd = dup(r->replaced_fd);
    if (r->duped_fd == -1)
    {
        fprintf(stderr, "fd duplication failed\n");
        return -1;
    }

    r->replaced_fd = dup2(r->source_fd, r->replaced_fd);
    if (r->replaced_fd == -1)
    {
        fprintf(stderr, "dup2 failed\n");
        return -1;
    }

    return 0;
}

int undo_redirection(struct redirection *r)
{
    // remplace 'replaced_fd' by the backup 'duped_fd'

    r->replaced_fd = dup2(r->duped_fd, r->replaced_fd);
    if (r->replaced_fd == -1)
    {
        fprintf(stderr, "restoring fd backup failed\n");
        return -1;
    }
    close(r->duped_fd);

    return 0;
}

void free_redirection(struct redirection *r)
{
    if (r != NULL)
    {
        if (r->source_fd != -1)
        {
            close(r->source_fd);
            r->source_fd = -1;
        }
        if (r->replaced_fd != -1)
        {
            close(r->replaced_fd);
            r->replaced_fd = -1;
        }
        free(r);
    }
}