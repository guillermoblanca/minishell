/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pipex_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:07:45 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:24:20 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen_b(const char *s)
{
	size_t	i;

	i = 0;
	while (((char *)s)[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat_b(char *dst, const char *src, size_t destsize)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	lendst = ft_strlen_b (dst);
	lensrc = ft_strlen_b (src);
	if (destsize > 0 && lendst < destsize - 1)
	{
		while (dst[i] != '\0')
			i++;
		while (src[c] != '\0' && c + i < destsize - 1)
		{
			dst[i + c] = src[c];
			c++;
		}
		dst [i + c] = '\0';
	}
	if (lendst >= destsize)
		lendst = destsize;
	return (lendst + lensrc);
}

char	*ft_strjoin_b(char const *s1, char const *s2)
{
	char	*j;
	int		i;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen_b(s1) + ft_strlen_b(s2) + 1;
	j = (char *)malloc(size);
	if (!j)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		j[i] = s1[i];
		i++;
	}
	j[i] = '\0';
	ft_strlcat_b(j, s2, size);
	return (j);
}

int	ft_strncmp_b(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2 [i]) && (s1[i] && s2[i] != '\0') && (i < n))
		i++;
	{
		if (i != n)
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		return (0);
	}
}
