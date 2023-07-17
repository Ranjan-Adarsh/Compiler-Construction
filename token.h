/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H


typedef struct Token {
    int token_type;
    char *lexeme;
    int line_number;
} Token;

Token *create_token_with_type_and_lexeme_for(int token_type);

#endif //COMPILER_TOKEN_H
