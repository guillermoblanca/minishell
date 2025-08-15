#include "exit.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

int parse_exit_arg(const char *arg, int *exit_code)
{
     long num = 0;
    char *endptr;

    if (!arg || *arg == '\0')
        return 0; // sin argumento, salir con last_exit_code

    num = strtol(arg, &endptr, 10);

    // Comprobar si hay caracteres no numéricos
    if (*endptr != '\0')
        return -1;

    // Ajustar al rango 0-255
    *exit_code = (int)(num % 256);
    if (*exit_code < 0)
        *exit_code += 256;

    return 0;
}

int builtin_exit(t_token *tokens, int last_exit_code)
{
    t_token *current = tokens->next; // saltar "exit"
    int code = last_exit_code;

    if (current)
    {
        int res = parse_exit_arg(current->value, &code);
        if (res == -1)
        {
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", current->value);
            return 2; // error de argumento
        }
        if (current->next)
        {
            fprintf(stderr, "minishell: exit: too many arguments\n");
            return 1;
        }
    }

    return code; // devolver código correcto
}