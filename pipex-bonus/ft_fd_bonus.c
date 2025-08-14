/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:07:31 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:01:45 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_infile_b(t_arg *a)
{
	a->fd1 = open(a->file1, O_RDONLY);
	if (a->fd1 < 0)
		ft_error_bonus(a, "open");
}

void	ft_outfile_heredoc(t_arg *a)
{
	if (access(a->file2, F_OK) != 0)
	{
		a->fd2 = open(a->file2, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (a->fd2 < 0)
			ft_error_bonus(a, "open");
	}
	else
	{
		a->fd2 = open(a->file2, O_WRONLY | O_APPEND, 0644);
		if (a->fd2 < 0)
			ft_error_bonus(a, "open");
	}
}

void	ft_outfile_b(t_arg *a)
{
	if (ft_strcmp(a->file1, ".heredoc_tmp") != 0)
	{
		if (access(a->file2, F_OK) != 0)
		{
			a->fd2 = open(a->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (a->fd2 < 0)
				ft_error_bonus(a, "open");
		}
		else
		{
			a->fd2 = open(a->file2, O_WRONLY | O_TRUNC, 0644);
			if (a->fd2 < 0)
				ft_error_bonus(a, "open");
		}
	}
	else
		ft_outfile_heredoc(a);
}
