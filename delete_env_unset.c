#include "structurescdmandshell.h"

void	ft_delete_env_unset(char **name, t_shell *shell)
{
	int	x;
	int	i;
	int	c;

	x = -1;
	while (name[++x] != NULL)
	{
		i = -1;
		while (shell->env[++i] != NULL)
		{
			if (!ft_strncmp(shell->env[i], name[x], ft_strlen(name[x]))
				&& shell->env[i][ft_strlen(name_var[x])] == '=')
			{
				free(shell->env[i]);
				c = i;
				while (shell->env[c] != NULL)
				{
					shell->env[c] = shell->env[c + 1];
					c++;
				}
				shell->env[c] = NULL;
				i--;
			}
		}
	}
}
