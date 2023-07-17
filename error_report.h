/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#include <stdio.h>

#ifndef COMPILER_ERROR_REPORT_H
#define COMPILER_ERROR_REPORT_H

#define MAX_ERROR_MESSAGE_LENGTH 256
typedef enum ErrorType {
    LEXICAL_ERROR,
    SYNTAX_ERROR,
    SEMANTIC_ERROR,
} ErrorType;


void report_error(ErrorType error_type, char *error_message);

#endif //COMPILER_ERROR_REPORT_H
