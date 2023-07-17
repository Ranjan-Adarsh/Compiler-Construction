/**
MANAF - 2019B3A70351P
ADARSH - 2019B3A70443P
NISHANT - 2019B3A70381P
**/
#ifndef COMPILER_ERRORS_H
#define COMPILER_ERRORS_H
typedef enum error {
    ERROR_OK = 0,
    ERROR_INVALID_INDEX,
    ERROR_EMPTY_LIST,
    ERROR_ALREADY_PRESENT,
    ERROR_EMPTY_STACK,
    ERROR_UNDETECTED,
    ERROR_WRONG_PRODUCTIONS_NUMBER,
    ERROR_CREATING_FIRST_SET,
    ERROR_CREATING_FOLLOW_SET,
    ERROR_READING_FILE,
    ERROR_READING_TERMINALS,
    ERROR_READING_NON_TERMINALS,
    ERROR_READING_PRODUCTION,
    ERROR_NO_MORE_CONTENT_IN_FILE,
    ERROR_INVALID_ARGS,
    ERROR_SYNTAX,
    ERROR_LEXICAL
} error;

void print_error(error err, char *message);

#endif //COMPILER_ERRORS_H