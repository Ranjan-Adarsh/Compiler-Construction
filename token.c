/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#include "token.h"
#include "utility.h"
#include "grammar_constants.h"

Token *create_token_with_type_and_lexeme_for(int token_type) {
    Token *token = malloc_safe(sizeof(Token));
    token->token_type = token_type;
    token->lexeme = strdup(SYMBOL_TO_STRING[token_type]);
    return token;
}