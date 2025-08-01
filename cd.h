#ifndef CD_H
# define CD_H

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
