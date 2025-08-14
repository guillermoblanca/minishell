/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:04:56 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 17:53:50 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_files(t_args *a)
{
	if (access(a->file1, F_OK) != 0)
	{
		ft_printf("Infile not found\n");
		ft_free_arg(a);
		exit(1);
	}
	if (access(a->file1, R_OK) != 0)
	{
		ft_printf("Infile permissions denied\n");
		ft_free_arg(a);
		exit(5);
	}
}

char	*ft_cmd(char *c, char *e)
{
	char	**h;
	char	*str;
	int		i;

	i = 0;
	str = ft_substr(e, 5, ft_strlen(e));
	h = ft_split(str, ':');
	free (str);
	while (h[i] != NULL)
	{
		str = ft_strjoin(h[i], c);
		if (access(str, F_OK | X_OK) == 0)
			break ;
		free (str);
		str = NULL;
		i++;
	}
	while (h[i] != NULL)
		i++;
	ft_free(h, i);
	return (str);
}

t_args	ft_arg(t_args *a, char **e)
{
	int	i;

	i = 0;
	ft_files(a);
	while (ft_strncmp(e[i], "PATH=", 5) != 0)
		i++;
	a->cmd1_path = ft_cmd(a->cmd1, e[i]);
	if (a->cmd1_path == NULL)
	{
		ft_printf("Command not found\n");
		ft_free_arg(a);
		exit(127);
	}
	a->cmd2_path = ft_cmd(a->cmd2, e[i]);
	if (a->cmd2_path == NULL)
	{
		ft_printf("Command not found\n");
		ft_free_arg(a);
		exit(127);
	}
	return (*a);
}
