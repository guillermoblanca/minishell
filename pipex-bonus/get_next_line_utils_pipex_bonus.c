/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_pipex_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:31:05 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/29 23:31:33 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

ssize_t	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == (char) c)
			return ((char *) &str[i]);
	return (NULL);
}

char	*ft_substr_gnl(char *str, unsigned int start, ssize_t len)
{
	char	*sub;
	ssize_t	i;

	i = -1;
	if (start >= ft_strlen_gnl(str))
		return (NULL);
	if (len + start > ft_strlen_gnl(str))
		len = ft_strlen_gnl(str) - start;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (++i < len)
		sub[i] = str[i + start];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup_gnl(char *str)
{
	char	*a;
	int		i;

	i = -1;
	a = (char *)malloc(sizeof(char) * ft_strlen_gnl(str) + 1);
	if (!a)
		return (NULL);
	while (str[++i])
		a[i] = str[i];
	a[i] = '\0';
	return (a);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	ssize_t	i;
	ssize_t	c;

	i = -1;
	c = -1;
	if (!s1)
		s1 = ft_strdup_gnl("");
	if (!s1)
		return (NULL);
	s3 = malloc(sizeof(char) * ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[++c])
		s3[i++] = s2[c];
	s3[i] = '\0';
	return (ft_freegnl(&s1), s3);
}
