#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_cmd
{
        char    *cmd;
        char    **args;
        char    **incmd;
        char    **outcmd;
}       t_cmd;


typedef struct s_shell
{
        int             exec_signal;
        int             exit;
        int             infd;
        int             nextinfd;
        int             outfd;
        int             g_status;
        int             infile;
        int             outfile;
        int             error_parse
        int             prev_fd;
        pid_t   pid;
        char    *oldpwd;
        char    *prompt_parse;
        char    *prompt;
        char    *cmd_path;
        char    **env;
        char    **full_cmd;
        char    **split_cmd;
        t_cmd   **cmds;
}                       t_shell;

int     ft_check_update(char *name, char *value, t_shell *shell);
void    ft_free_env(char **env);
char    *ft_new(char *name, char *value);
void    ft_create_env(char *name, char *value, t_shell *shell);
void    ft_update_env(char *command, t_shell *shell);
void    ft_delete_env_unset(char **name, t_shell *shell);
void    error_env(char *command, int i);
void    error1_env(char *command, int i);
void    error2_env(char *command, int i);
void    env_err3(void);
int     check_env(char *env);
void    ft_print_env_error(t_shell *shell, int env_error, char *command);
void    ft_print_env(t_shell *shell);
void    ft_error_env_print(t_shell *shell, char *path);
int     ft_path_checking(t_shell *shell, char **path);
void    ft_env_print(t_shell *shell, char **path);

void    print_cd_error(t_shell *shell);
void    print_backpwd_error(char *back, t_shell *shell);
void    print_home_error(char *home, t_shell *shell);
void    error_too_many_args(t_shell *shell);
void    cd_dash_error(t_shell *shell);
char    *ft_get_env(char *str, char **env_path);
void    ft_back_pwd(t_shell *shell);
void    ft_home_cd(t_shell *shell);
void    update_pwd(t_shell *shell);
void    ft_cd(char **command, t_shell *shell);




# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

#endif
