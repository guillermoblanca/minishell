/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:03:09 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/23 16:07:19 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_initialize(t_args *a)
{
	a->cmd1 = NULL;
	a->cmd2 = NULL;
	a->cmd1_path = NULL;
	a->cmd2_path = NULL;
	a->command1 = NULL;
	a->command2 = NULL;
	a->file1 = NULL;
	a->file2 = NULL;
	a->fd1 = 0;
	a->fd2 = 0;
}

void	ft_parse_arg(t_args *a, char **argv)
{
	int	i;

	i = 1;
	ft_initialize(a);
	a->file1 = argv[i++];
	a->command1 = ft_split(argv[i++], ' ');
	if (!a->command1)
		ft_error(a, "ft_split");
	a->cmd1 = ft_strjoin("/", a->command1[0]);
	if (!a->cmd1)
		ft_error(a, "ft_strjoin");
	a->command2 = ft_split(argv[i++], ' ');
	if (!a->command2)
		ft_error(a, "ft_split");
	a->cmd2 = ft_strjoin("/", a->command2[0]);
	if (!a->cmd2)
		ft_error(a, "ft_strjoin");
	a->file2 = argv[i++];
}
