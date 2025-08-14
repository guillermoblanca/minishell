/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:05:09 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 17:29:13 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_args *a, char *e)
{
	perror(e);
	ft_free_arg(a);
	exit(EXIT_FAILURE);
}

void	ft_child(t_args *a, int pfd[2], char **c)
{
	pid_t	p;

	p = fork();
	if (p == -1)
		ft_error(a, "fork");
	if (p == 0)
	{
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			ft_error(a, "dup2");
		close(pfd[0]);
		if (execve(a->cmd1_path, a->command1, c) == -1)
			ft_error(a, "execve");
	}
	else
	{
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			ft_error(a, "dup2");
		waitpid(p, NULL, 0);
	}
}

void	ft_infile(t_args *a)
{
	a->fd1 = open(a->file1, O_RDONLY);
	if (a->fd1 < 0)
		ft_error(a, "open");
}

void	ft_outfile(t_args *a)
{
	if (access(a->file2, F_OK) != 0)
	{
		a->fd2 = open(a->file2, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (a->fd2 < 0)
			ft_error(a, "open");
	}
	else
	{
		a->fd2 = open(a->file2, O_WRONLY | O_TRUNC);
		if (a->fd2 < 0)
			ft_error(a, "open");
	}
}
