#include <stdio.h>

#include "io.h"
#include "lexer.h"
#include "tokens.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: token_printer [COMMAND]");
        return 1;
    }

    /*
    TOKEN_ERROR,
    TOKEN_IF,           // if keyword
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_SEMICOL,      // ; token
    TOKEN_EOL,          // \n token
    TOKEN_EOF,          // EOF token
    TOKEN_SINGLEQUOTE,  // ' token
    TOKEN_WORDS         // identifier token, ex : variable name
    TOKEN_FRED_OUT,     // > token (read F(ile) RED(irection) OUT)
    TOKEN_FRED_IN,      // < token
    TOKEN_FDRED_OUT,    // >& token (F(ile)D(escriptor) RED(irection) OUT)
    TOKEN_FDRED_IN,     // <& token
    TOKEN_FRED_APP,     // >> token (F(file) RED(irection) APP(end), redirect to
    file and append to it) TOKEN_BIRED,        // <> token, no idea what this is
    used for but well TOKEN_FRED_FORCE,   // >| token, force truncating output
    file (search google for set -o)
    */

    char *tab[] = {
        [TOKEN_ERROR] = "ERROR",
        [TOKEN_WORDS] = "WORD",
        [TOKEN_IO_NUMBER] = "IO_NUMBER",
        [TOKEN_EOF] = "EOF",
        [TOKEN_EOL] = "EOL",
        [TOKEN_SEMICOL] = ";",
        [TOKEN_IF] = "if",
        [TOKEN_ELIF] = "elif",
        [TOKEN_ELSE] = "else",
        [TOKEN_THEN] = "then",
        [TOKEN_FI] = "fi",
        [TOKEN_FRED_OUT] = ">",
        [TOKEN_FRED_IN] = "<",
        [TOKEN_FDRED_OUT] = ">&",
        [TOKEN_FDRED_IN] = "<&",
        [TOKEN_FRED_APP] = ">>",
        [TOKEN_BIRED] = "<>",
        [TOKEN_FRED_FORCE] = ">|",
        [TOKEN_WHILE] = "while",
        [TOKEN_UNTIL] = "until",
        [TOKEN_DO] = "do",
        [TOKEN_DONE] = "done",
    };

    struct INPUT *input = input_from_string(argv[1]);
    struct lexer *lexer = lexer_new(input);

    struct token *token;
    enum token_type type = TOKEN_ERROR;
    while (type != TOKEN_EOF)
    {
        token = lexer_pop(lexer);
        type = token->type;
        printf("%s", tab[type]);
        if (type == TOKEN_ERROR)
            break;
        if (type == TOKEN_WORDS || type == TOKEN_IO_NUMBER)
            printf(" (%s)", token->value);
        printf("\n");
    }

    return 0;
}