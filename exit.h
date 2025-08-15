#ifndef EXIT_H
#define EXIT_H

#include "lexer.h"

int parse_exit_arg(const char *arg, int *exit_code);
int builtin_exit(t_token *tokens, int last_exit_code);
#endif