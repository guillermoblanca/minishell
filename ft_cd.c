#include "builtins.h"

char	*ft_get_env(char *str, char **env_path)
{
	int		i;
	int		c;
	char	*path;

	i = 0;
	while (env_path[i] != NULL)
	{
		c = 0;
		while (env_path[i][c] == str[c] && str[c] != '\0')
			c++;
		if (env_path[i][c] == '=' && str[c] == '\0')
		{
			c++;
			path = ft_strdup(env_path[i] + c);
			if (path == NULL)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	ft_back_pwd(t_shell *shell)
{
	char	*back;

	back = ft_get_env("OLDPWD", shell->env);
	if (back == NULL)
		return (cd_dash_error(shell));
	if (chdir(back) == -1)
		print_backpwd_error(back, shell);
	write(shell->outfd, back, ft_strlen(back));
	write(shell->outfd, "\n", 2);
	free(back);
}

void	ft_home_cd(t_shell *shell)
{
	char	*home;

	home = ft_get_env("HOME", shell->env);
	if (home == NULL)
		return ;
	if (chdir(home) == -1)
		print_home_error(home, shell);
	free(home);
}


void	update_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (print_cd_error(shell));
	while (shell->env[i] != NULL)
	{
		if (strncmp(shell->env[i], "PWD", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", cwd);
			if (shell->env[i] == NULL)
			{
				shell->g_status = 1;
				return ;
			}
			return ;
		}
		i++;
	}
}

void	ft_cd(char **command, t_shell *shell)
{
	if (command[1] != NULL)
		return (error_too_many_args(shell));
	shell->oldpwd = ft_get_env("PWD", shell->env);
	if (command[0] == NULL || command[0][0] == '~')
		ft_home_cd(shell);
	else if (command[0][0] == '-')
		ft_back_pwd(shell);
	else
	{
		if (chdir(command[0]) == -1)
		{
			write(STDERR_FILENO, "cd: no such file or directory: ", 31);
			write(STDERR_FILENO, command[0], ft_strlen(command[0]));
			write(STDERR_FILENO, "\n", 2);
			shell->g_status = 1;
		}
	}
	if (shell->g_status == 1)
	{
		free(shell->oldpwd);
		shell->oldpwd = NULL;
	}
	else
		update_pwd(shell);
}
