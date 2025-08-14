/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:01:42 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 17:54:36 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(t_args *a, char **e)
{
	pid_t	p;
	int		pfd[2];

	if (pipe (pfd) == -1)
		ft_error (a, "pipe");
	if (dup2(a->fd1, STDIN_FILENO) == -1)
		ft_error(a, "dup2");
	ft_child(a, pfd, e);
	if (dup2(a->fd2, STDOUT_FILENO) == -1)
		ft_error(a, "dup2");
	p = fork();
	if (p == -1)
		ft_error(a, "fork");
	if (p == 0)
	{
		if (execve(a->cmd2_path, a->command2, e) == -1)
			ft_error(a, "execve");
	}
	else
		waitpid(p, NULL, 0);
}

int	main(int argc, char **argv, char **e)
{
	t_args	*a;

	if (e[0] == NULL)
		return (0);
	if (argc == 5)
	{
		a = malloc(sizeof(t_args));
		if (!a)
			ft_error(a, "malloc");
		ft_parse_arg(a, argv);
		*a = ft_arg(a, e);
		ft_infile(a);
		ft_outfile(a);
		ft_pipex(a, e);
		ft_free_arg(a);
	}
	else
	{
		ft_printf("Error: Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
