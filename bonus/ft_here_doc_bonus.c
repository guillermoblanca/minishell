/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:03:42 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:30:07 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_initialize_bn(t_arg *a)
{
	a->cmd = NULL;
	a->cmdpath = NULL;
	a->command = NULL;
	a->firstcmd = NULL;
	a->firstpath = NULL;
	a->firstcommand = NULL;
	a->file1 = NULL;
	a->file2 = NULL;
	a->limit = NULL;
	a->cmd_n = 0;
	a->index = 0;
	a->fd1 = 0;
	a->fd2 = 0;
	a->heredocflag = 0;
}

void	ft_heredoc_init(t_arg *a, char **argv, int argc)
{
	int			i;
	t_command	*aux_cmd;
	t_list		*aux;
	t_list		*f;

	i = 2;
	aux = NULL;
	f = NULL;
	ft_initialize_bn(a);
	a->heredocflag = 1;
	a->file1 = ".heredoc_tmp";
	a->limit = argv[i++];
	while (i < argc - 1)
	{
		aux_cmd = ft_new_cmd(argv[i++]);
		ft_add_back(&a->command, aux_cmd);
		aux = ft_lstnew(ft_strjoin_b("/", aux_cmd->cmd[0]));
		if (!f)
			f = aux;
		ft_lstadd_back(&a->cmd, aux);
	}
	a->file2 = argv[i];
	a->cmd = f;
}

void	ft_heredoc(t_arg *a, char **argv, int argc)
{
	int		fd;
	char	*b;

	ft_heredoc_init(a, argv, argc);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_error_bonus(a, "open");
	while (1)
	{
		ft_printf_b("heredoc> ");
		b = get_next_line_p(STDIN_FILENO);
		if (!ft_strncmp_b(a->limit, b, ft_strlen_b(a->limit))
			&& ft_strlen_b(b) - 1 == ft_strlen_b(a->limit))
			break ;
		write(fd, b, ft_strlen_b(b));
		free(b);
	}
	free(b);
	close(fd);
	a->fd1 = open(".heredoc_tmp", O_RDONLY);
	if (a->fd1 < 0)
	{
		unlink(".heredoc_tmp");
		ft_error_bonus(a, "open");
	}
}
