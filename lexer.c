#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "command.h"

t_token *create_token(t_token_type type, const char *value)
{
    t_token *token = (t_token *)malloc(sizeof(t_token));

    if (!token)
        return NULL;
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

t_token *add_token(t_token **last, t_token *new_token)
{
    if (*last)
    {
        (*last)->next = new_token;
    }
    *last = new_token;
    return new_token;
}

t_token_type get_redir_type(const char *op)
{
    if (strcmp(op, ">") == 0)
    {
        return TOKEN_REDIR_OUT;
    }
    if (strcmp(op, ">>") == 0)
    {
        return TOKEN_REDIR_OUT_APPEND;
    }
    if (strcmp(op, "<") == 0)
    {
        return TOKEN_REDIR_IN;
    }
    if (strcmp(op, "<<") == 0)
    {
        return TOKEN_HEREDOC;
    }
    return TOKEN_WORD;
}

char **tokens_to_argv(t_token *tokens)
{
    int count = 0;
    t_token *tmp = tokens;

    while (tmp)
    {
        if (tmp->type == TOKEN_WORD)
            count++;
        tmp = tmp->next;
    }

    char **argv = malloc(sizeof(char *) * (count + 1));
    tmp = tokens;
    int i = 0;
    while (tmp)
    {
        if (tmp->type == TOKEN_WORD)
        {
            argv[i++] = strdup(tmp->value);
        }
        tmp = tmp->next;
    }
    argv[i] = NULL;
    return argv;
}

t_token *lexer(const char *input)
{
    t_token *head = NULL;
    t_token *last = NULL;
    int i = 0;
    while (input[i])
    {
        // comprueba si el siguiente caracter es un espacio y si lo es pasamos al siguiente caracter
        if (isspace(input[i]))
        {
            i++;
            continue;
            ;
        }

        // PIPE
        if (input[i] == '|')
        {
            add_token(&last, create_token(TOKEN_PIPE, "|"));
            if (!head)
            {
                head = last;
            }
            i++;
        }
        else if (input[i] == '<' || input[i] == '>')
        {
            // en 42 no se admite declarar variables fuera de la cabecera de la funcion
            char op[3] = {input[i], 0, 0};
            if (input[i + 1] == input[i])
            {
                op[1] = input[i];
                i++;
            }
            add_token(&last, create_token(get_redir_type(op), op));
            if (!head)
                head = last;
            i++;
        }
        else
        { // echo
            char buffer[1024];
            int buf_index = 0;
            int in_quote = 0;
            char quote_char = 0;

            while (input[i] && (in_quote || (!isspace(input[i]) && input[i] != '|' && input[i] != '<' && input[i] != '>')))
            {
                if ((input[i] == '\'' || input[i] == '"'))
                {
                    if (!in_quote)
                    {
                        in_quote = 1;
                        quote_char = input[i];
                        i++;
                        continue;
                    }
                    else if (quote_char == input[i])
                    {
                        in_quote = 0;
                        i++;
                        continue;
                    }
                }
                buffer[buf_index++] = input[i++];
            }

            buffer[buf_index] = '\0';
            add_token(&last, create_token(TOKEN_WORD, buffer));
            if (!head)
                head = last;
        }
    }
    return head;
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
}

void expand_env_variables(t_token *tokens)
{
    while (tokens)
    {
        if ((tokens->type == TOKEN_WORD || tokens->type == TOKEN_WORD_DOUBLE_QUOTED)
            && tokens->value[0] == '$' && tokens->value[1] != '\0')
        {
            char *env_name = tokens->value + 1;
            char *env_value = NULL;

            if (strcmp(env_name, "?") == 0)
            {
                char buffer[12];
                snprintf(buffer, sizeof(buffer), "%d", get_last_exit_code());
                env_value = strdup(buffer);
            }
            else
            {
                char *env = getenv(env_name);
                env_value = env ? strdup(env) : strdup("");
            }

            free(tokens->value);
            tokens->value = env_value;
        }
        tokens = tokens->next;
    }
}
