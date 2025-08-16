#ifndef LEXER_H
#define LEXER_H

/*
TODO: 
- sustituir strdup por funcion propia
- lectura de linea con getnextline
- cambiar variables locales a 42 lectura
*/

typedef enum e_token_type{
    TOKEN_WORD,
    TOKEN_WORD_SINGLE_QUOTED,  // texto entre comillas simples '...'
    TOKEN_WORD_DOUBLE_QUOTED,  // texto entre comillas dobles "..."
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_OUT_APPEND,
    TOKEN_REDIR_IN,
    TOKEN_HEREDOC,
} t_token_type;

typedef struct s_env{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_token{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

void free_tokens(t_token *tokens);
void expand_env_variables(t_token *tokens);
char **tokens_to_argv(t_token *tokens);
t_token *create_token(t_token_type type, const char *value);
t_token *add_token(t_token **last, t_token *new_token);
t_token_type get_redir_type(const char *op);
t_token *lexer(const char *input);


//unset functions
int builtin_unset(t_token *tokens, t_env **env);
int builtin_exit(t_token *tokens, int last_status);
void remove_env(t_env **env, const char *key);

//EXPORT
t_env *init_env(char **envp); //necesario?
int builtin_export(t_token *tokens, t_env **env);
int is_valid_identifier(const char *s);
t_env *find_env(t_env *env, const char *key);
void set_env(t_env **env, const char *key, const char *value);
t_env *init_env(char **envp);

#endif