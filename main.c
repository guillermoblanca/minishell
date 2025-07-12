#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
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

int main(void)
{
    char *line;
    t_token *tokens;
    print_header();

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

    return 0;
}
