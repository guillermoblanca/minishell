#ifndef ENV_H
# define ENV_H

int	ft_check_update(char *name, char *value, t_shell *shell);
void	ft_free_env(char **env);
char	*ft_new(char *name, char *value);
void	ft_create_env(char *name, char *value, t_shell *shell);
void	ft_update_env(char *command, t_shell *shell);
void	ft_delete_env_unset(char **name, t_shell *shell);
void	error_env(char *command, int i);
void	error1_env(char *command, int i);
void	error2_env(char *command, int i);
void	env_err3(void);
int	check_env(char *env);
void	ft_print_env_error(t_shell *shell, int env_error, char *command);
void	ft_print_env(t_shell *shell);
void	ft_error_env_print(t_shell *shell, char *path);
int	ft_path_checking(t_shell *shell, char **path);
void	ft_env_print(t_shell *shell, char **path);

# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

#endif
