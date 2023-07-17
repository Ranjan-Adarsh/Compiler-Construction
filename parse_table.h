/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_PARSE_TABLE_H
#define COMPILER_PARSE_TABLE_H

#include <stdlib.h>
#include "cfg.h"

Production ***get_parse_table_for(const Grammar *g);

void print_parse_table(Grammar *g, Production ***table, char *file);

void destroy_parse_table(const Grammar *g, Production ***parse_table);

#endif //COMPILER_PARSE_TABLE_H
