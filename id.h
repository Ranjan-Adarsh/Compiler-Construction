/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_ID_H
#define COMPILER_ID_H

#include "ast.h"

IDNode *create_id_node();

IDNode *create_id_node_with_token(Token *token);

#endif //COMPILER_ID_H
