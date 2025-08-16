#ifndef COMMAND_H
#define COMMAND_H
#include "lexer.h"

typedef struct s_minishell
{
    int state; // define el ultimo estado en el que se encuentra la minishell
} t_minishell;

typedef struct s_command
{
    char **argv;            // array de strings
    int argc;               // numero de argumentos
    int fd_in;              // file descriptor de entrada
    int fd_out;             // file descriptor de salida
    struct s_command *next; // para comands conectados por pipe
} t_command;

#define EXPORT_COMMAND "export"
#define UNSET_COMMAND "unset"
#define EXIT_COMMAND "exit"

int get_last_exit_code();
void execute_pipeline(char **argv1, char **argv2);
void execute_command(char **argv, char *output_file, t_token_type redir_type);

// TODO: comprobar si existen memory leaks
int process_command(t_token *tokens, t_env **env_list);
void print_header();
#endif