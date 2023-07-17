/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_ACTION_UTILITY_H
#define COMPILER_ACTION_UTILITY_H

#include "cfg.h"

int get_next_rhs_i_position_from_and_including(Production *production, int i);

int get_second_last_rhs_position(Production *production);

int get_last_rhs_position(Production *production);

#endif //COMPILER_ACTION_UTILITY_H
