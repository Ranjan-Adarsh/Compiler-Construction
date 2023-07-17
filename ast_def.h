/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_AST_DEF_H
#define COMPILER_AST_DEF_H


#include "token.h"

typedef struct Visitor Visitor;
typedef struct Range {
    Token *begin;
    Token *end;
    Token *begin_sign;
    Token *end_sign;
} Range;
#endif //COMPILER_AST_DEF_H
