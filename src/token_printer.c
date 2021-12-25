#include <stdio.h>

#include "tokens.h"
#include "lexer.h"
#include "io.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: token_printer [COMMAND]");
        return 1;   
    }

    /*
    TOKEN_ERROR,
    TOKEN_IF,          // if keyword
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_SEMICOL,     // ; token
    TOKEN_EOL,         // \n token
    TOKEN_EOF,         // EOF token
    TOKEN_SINGLEQUOTE, // ' token
    TOKEN_WORDS        // identifier token, ex : variable name
    */

    char *tab[] = { 
        [TOKEN_ERROR] = "ERROR", 
        [TOKEN_WORDS] = "WORD", 
        [TOKEN_EOF] = "EOF",
        [TOKEN_SEMICOL] = ";",
    };

    struct INPUT *input = input_from_string(argv[1]);
    struct lexer *lexer = lexer_new(input);

    struct token *token;
    enum token_type type = TOKEN_ERROR;
    while (type != TOKEN_EOF)
    {
        token = lexer_pop(lexer);
        type = token->type;
        printf("%s\n", tab[type]);
        if (type == TOKEN_ERROR)
            break;
        if (type == TOKEN_WORDS)
            printf("    value: %s\n", token->value);
    } 

    return 0;
}