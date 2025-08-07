/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:09:31 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:02:54 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_clear_list(t_list **a)
{
	t_list	*aux;

	if (!a)
		return ;
	while (*a)
	{
		aux = (*a)->next;
		free((*a)->content);
		free(*a);
		*a = aux;
	}
	*a = NULL;
}

void	ft_path_free(t_arg *a)
{
	t_list	*aux;

	aux = a->cmdpath;
	while (a->cmdpath)
	{
		free(a->cmdpath->content);
		a->cmdpath = a->cmdpath->next;
	}
	a->cmdpath = aux;
	ft_clear_list(&a->cmdpath);
}

void	*ft_free_b(char **str, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	*ft_free_arg_bonus(t_arg *a)
{
	int			i;
	t_command	*aux;

	ft_clear_list(&a->cmd);
	if (a->cmdpath)
		ft_clear_list(&a->cmdpath);
	while (a->command)
	{
		i = 0;
		while (a->command->cmd[i])
			i++;
		ft_free_b(a->command->cmd, i);
		aux = a->command->next;
		free(a->command);
		a->command = aux;
	}
	if (!a->firstcommand)
		exit(1);
	exit(0);
	return (NULL);
}
