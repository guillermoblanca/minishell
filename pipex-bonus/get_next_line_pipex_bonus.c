/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_pipex_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:31:52 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/29 23:35:04 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_freegnl(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_line(char *buffer, char **l)
{
	char	*r;
	int		i;

	r = NULL;
	i = ft_strlen_gnl(buffer);
	if (!buffer || !l)
		return (NULL);
	if (ft_strchr_gnl(buffer, '\n'))
	{
		r = ft_strdup_gnl(ft_strchr_gnl(buffer, '\n') + 1);
		(*l) = ft_substr_gnl(buffer, 0, i - ft_strlen_gnl(r));
	}
	else
	{
		(*l) = ft_substr_gnl(buffer, 0, i);
	}
	ft_freegnl(&buffer);
	return (r);
}

char	*ft_readfile(int fd, char *r)
{
	ssize_t		readbytes;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	readbytes = 1;
	buffer[0] = '\0';
	while (!ft_strchr_gnl(buffer, '\n') && readbytes != 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
		{
			ft_freegnl(&buffer);
			ft_freegnl(&r);
			return (NULL);
		}
		buffer[readbytes] = '\0';
		if (readbytes > 0)
			r = ft_strjoin_gnl(r, buffer);
	}
	ft_freegnl(&buffer);
	return (r);
}

char	*get_next_line_p(int fd)
{
	static char		*buffer;
	char			*l;

	l = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer || !ft_strchr_gnl(buffer, '\n'))
		buffer = ft_readfile(fd, buffer);
	if (!buffer)
		return (NULL);
	buffer = ft_line(buffer, &l);
	return (l);
}
