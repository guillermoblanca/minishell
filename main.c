#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "exit.h"
#include "command.h"

void print_header()
{
    FILE *file;
    char line[256];

    file = fopen("header.txt", "r");
    if (file == NULL)
        return;

    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    fclose(file);
}

void print_tokens(t_token *token)
{
    const char *names[] = {
        "WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC"};

    while (token)
    {
        printf("Token: %-10s | Value: \"%s\"\n", names[token->type], token->value);
        token = token->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_token *tokens;
    print_header();

    t_env *env_list = init_env(envp);
    (void)argc;
    (void)argv;
    int last_exit_code = 0;

    while (1)
    {
        line = readline("minishell >");
        if (!line) // Ctrl+D o EOF
        {
            printf("exit\n");
            break;
        }

        if (*line)
            add_history(line);

        tokens = lexer(line);

        if (tokens && tokens->type == TOKEN_WORD)
        {
            if (strcmp(tokens->value, "export") == 0)
            {
                builtin_export(tokens, &env_list);
                free_tokens(tokens);
                free(line);
                continue;
            }
            else if (strcmp(tokens->value, "unset") == 0)
            {
                builtin_unset(tokens, &env_list);
                free_tokens(tokens);
                free(line);
                continue;
            }
            else if (strcmp(tokens->value, "exit") == 0)
            {
                int exit_status = builtin_exit(tokens, 0 /* aquí puedes pasar last_exit_code */);
                free_tokens(tokens);
                free(line);
                if (exit_status != 1) // si no es "too many arguments"
                    return exit_status;
                else
                    continue;
            }
        }

        // print_tokens(tokens); // Debug
        char *output_file = NULL;
        t_token_type redir_type = -1;

        t_token *tmp = tokens;
        while (tmp)
        {
            if (tmp->type == TOKEN_REDIR_OUT || tmp->type == TOKEN_REDIR_OUT_APPEND)
            {
                if (tmp->next && tmp->next->type == TOKEN_WORD)
                {
                    output_file = strdup(tmp->next->value);
                    redir_type = tmp->type;
                    tmp->type = -1;
                    tmp->next->type = -1;
                    tmp = tmp->next;
                }
            }
            tmp = tmp->next;
        }

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
