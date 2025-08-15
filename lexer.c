#include "lexer.h"
#include "exit.h"
#include "ft_printf.h"
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
        if ((tokens->type == TOKEN_WORD || tokens->type == TOKEN_WORD_DOUBLE_QUOTED) && tokens->value[0] == '$' && tokens->value[1] != '\0')
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

// TODO: move to export_lib.c

static int env_count(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}

static void print_export_sorted(t_env *env)
{
    int n = env_count(env);
    t_env **arr = malloc(sizeof(t_env *) * n);
    int i = 0;

    while (env)
    {
        arr[i++] = env;
        env = env->next;
    }

    for (int a = 0; a < n - 1; a++)
        for (int b = 0; b < n - a - 1; b++)
            if (strcmp(arr[b]->key, arr[b + 1]->key) > 0)
            {
                t_env *tmp = arr[b];
                arr[b] = arr[b + 1];
                arr[b + 1] = tmp;
            }

    for (i = 0; i < n; i++)
    {
        if (arr[i]->value)
            printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
        else
            printf("declare -x %s\n", arr[i]->key);
    }

    free(arr);
}
int is_valid_identifier(const char *str)
{
    if (!str || (!isalpha(str[0]) && str[0] != '_'))
        return 0;
    for (int i = 1; str[i]; i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    return 1;
}

int builtin_unset(t_token *tokens, t_env **env)
{
    t_token *current = tokens->next; // saltar "unset"

    if (!current)
        return 0; // sin argumentos, exit code = 0

    while (current)
    {
        if (current->type == TOKEN_WORD)
        {
            remove_env(env, current->value); // tu función que borra la variable
        }
        current = current->next;
    }
    return 0; // siempre exit code 0
}

void remove_env(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;

            free(current->key);
            free(current->value);
            free(current);
            return; // variable eliminada
        }
        prev = current;
        current = current->next;
    }
    // si no se encontró, no hace nada
}


int builtin_export(t_token *tokens, t_env **env)
{
    t_token *current = tokens->next; // saltar "export"
    int status = 0;

    // Sin argumentos: mostrar lista exportada
    if (!current)
    {
        print_export_sorted(*env);
        return 0;
    }

    while (current)
    {
        if (current->type == TOKEN_WORD)
        {
            char *equal = strchr(current->value, '=');
            char *key;
            char *value = NULL;

            if (equal)
            {
                key = ft_substr(current->value, 0, equal - current->value);
                value = strdup(equal + 1);
            }
            else
            {
                key = strdup(current->value);
            }

            if (!is_valid_identifier(key))
            {
                fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", current->value);
                status = 1; // marcar error pero continuar con los demás
            }
            else
            {
                set_env(env, key, value);
            }

            free(key);
            free(value);
        }
        current = current->next;
    }
    return status;
}


t_env *init_env(char **envp)
{
    t_env *env_list = NULL;
    int i = 0;

    while (envp[i])
    {
        char *equal = strchr(envp[i], '=');
        if (equal)
        {
            char *key = ft_substr(envp[i], 0, equal - envp[i]);
            char *value = strdup(equal + 1);
            set_env(&env_list, key, value);
            free(key);
            free(value);
        }
        i++;
    }
    return env_list;
}



t_env *find_env(t_env *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

void set_env(t_env **env, const char *key, const char *value)
{
    t_env *var = find_env(*env, key);

    if (var)
    {
        free(var->value);
        var->value = value ? strdup(value) : NULL;
    }
    else
    {
        t_env *new = malloc(sizeof(t_env));
        new->key = strdup(key);
        new->value = value ? strdup(value) : NULL;
        new->next = *env;
        *env = new;
    }
}
