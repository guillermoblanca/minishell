#include "structurescdmandshell.h"

int	check_env(char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]))
		return (0);
	if (env[i] == '=')
		return (-3);
	while (env[i])
	{
		if (env[i] == '=')
		{
			if (env[i + 1] == '=' && env[i + 2] != '\0')
				return (-2);
		}
		i++;
	}
	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			return (-1);
		i++;
	}
	return (1);
}
void	ft_print_env_error(t_shell *shell, int env_error, char *command)
{
	int	i;

	i = 0;
	shell->g_status = 1;
	if (env_err == 0)
		error_env(command, i);
	else if (env_err == -3)
	{
		if (command[1] != '\0')
			error1_env = -2;
		else
			error3_env();
	}
	else if (env_err == -1)
		error1_env(command, i);
	else if (env_err == -2)
		error2_env(command, i);
}
void	ft_print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		write(shell->outfd, "declare -x ", 11);
		write(shell->outfd, shell->env[i], ft_strlen(shell->env[i]));
		write(shell->outfd, "\n", 1);
		i++;
	}
}
