/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_SEMANTIC_ANALYZER_H
#define COMPILER_SEMANTIC_ANALYZER_H

#include "symbol_table.h"
#include "ast.h"

extern bool GOT_SEMANTIC_ERROR_GLOBAL;
void perform_semantic_analysis(ProgramNode *root, SymbolTable *global_symbol_table_parameter);

#endif //COMPILER_SEMANTIC_ANALYZER_H
