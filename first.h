/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_FIRST_H
#define COMPILER_FIRST_H

#include "hashset.h"
#include "hashmap.h"
#include "cfg.h"

error set_first_sets_for(Grammar *g);

HashSet *first_set_of_symbols(const Grammar *g, int symbols[], int size);

#endif //COMPILER_FIRST_H
