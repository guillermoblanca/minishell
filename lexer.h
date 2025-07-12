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
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,      // >
    TOKEN_REDIR_OUT_APPEND, // >>
    TOKEN_REDIR_IN,       // <
    TOKEN_HEREDOC  
} t_token_type;

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
#endif