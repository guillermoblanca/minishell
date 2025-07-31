#include "structurescdmandshell.h"

void	ft_error_env_print(t_shell *shell, char *path)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	shell->g_status = 127;
	return (FAILURE);
}

int	ft_path_checking(t_shell *shell, char **path)
{
	int	i;
	int	c;
	int	flag;

	i = 0;
	while (path[i] != NULL)
	{
		c = 0;
		flag = 1;
		while (path[i][c])
		{
			if (path[i][c] == '=')
				flag = 0;
			c++;
			if (flag == 1 && path[i][c] == '\0')
				return (ft_error_env_print(shell, path[i]));
		}
		i++;
	}
	return (SUCCESS);
}

void	ft_env_print(t_shell *shell, char **path)
{
	int	i;

	i = 0;
	if (ft_path_checking(shell, path) == 0)
	{
		while (shell->env[i])
		{
			write(shell->outfd, shell->env[i], ft_strlen(shell->env[i]));
			write(shell->outfd, "\n", 1);
			i++;
		}
		i = 0;
		while (paths[i])
		{
			write(shell->outfd, path[i], ft_strlen(path[i]));
			write(shell->outfd, "\n", 1);
			i++;
		}
	}
}

