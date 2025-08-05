#include "builtins.h"

int	ft_check_update(char *name, char *value, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin(name, "=");
			if (value)
			{
				free(shell->env[i]);
				shell->env[i] = ft_strjoin(shell->env[i], value);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*ft_new(char *name, char *value)
{
	char	*new;

	new = ft_strjoin(name, "=");
	if (value)
		new = ft_strjoin(new, value);
	return (new);
}

void	ft_create_env(char *name, char *value, t_shell *shell)
{
	int		i;
	char	**new;

	i = 0;
	while (shell->env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	i = 0;
	while (shell->env[i])
	{
		new[i] = ft_strdup(shell->env[i]);
		i++;
	}
	new[i++] = ft_new(name, value);
	new[i] = NULL;
	ft_free_env(shell->env);
	shell->env = new_env;
}

void	ft_update_env(char *command, t_shell *shell)
{
	char	*equal;
	char	*name;
	char	*value;

	equal = ft_strchr(command, '=');
	if (equal)
	{
		*equal = '\0';
		name = command;
		value = equal + 1;
		if (!ft_check_update(name, value, shell))
			ft_create_env(name, value, shell);
	}
}
