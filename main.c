#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "exit.h"
#include "command.h"

void pipe_update(t_token *tokens, t_token_type *redir_type, char **output_file)
{
    t_token *tmp = tokens;
    while (tmp)
    {
        if (tmp->type == TOKEN_REDIR_OUT || tmp->type == TOKEN_REDIR_OUT_APPEND)
        {
            if (tmp->next && tmp->next->type == TOKEN_WORD)
            {
                free(*output_file);
                *output_file = strdup(tmp->next->value);
                *redir_type = tmp->type;
                tmp->type = -1;
                tmp->next->type = -1;
                tmp = tmp->next;
            }
        }
        tmp = tmp->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_token *tokens;
    t_env *env_list = init_env(envp);
    int last_exit_code = 0;
    (void)argc;
    (void)argv;

    print_header();

    while (1)
    {

        line = readline("minishell >");
        if (!line)
        {
            printf("exit\n");
            break;
        }

        if (*line)
            add_history(line);

        tokens = lexer(line);

        if (tokens && tokens->type == TOKEN_WORD)
        {
            last_exit_code = process_command(tokens, &env_list);
            if (last_exit_code != 0) // export/unset usan 1, exit devuelve código real
            {

                if (strcmp(tokens->value, EXIT_COMMAND) == 0 && last_exit_code != 1)
                {
                    exit(last_exit_code); // salir de verdad
                }
            }
        }

        if (!tokens)
            continue;

        char *output_file = NULL;
        t_token_type redir_type = -1;
        pipe_update(tokens, &redir_type, &output_file);
        expand_env_variables(tokens);
        char **argv = tokens_to_argv(tokens);
        execute_command(argv, output_file, redir_type);
        if (argv)
        {
            int j = 0;
            while (argv[j] != NULL)
            {
                free(argv[j]);
                j++;
            }
            free(argv);
        }

        free_tokens(tokens);
        free(line);
    }

    return (last_exit_code);
}
