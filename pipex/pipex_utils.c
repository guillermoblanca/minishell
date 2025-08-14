/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:15:14 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 17:45:49 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (((char *)s)[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	lendst = ft_strlen (dst);
	lensrc = ft_strlen (src);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j;
	int		i;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
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
	ft_strlcat(j, s2, size);
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	c;
	char	*p;

	i = 0;
	c = 0;
	if (start > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		if (i >= start && c < len)
		{
			p[c] = s[i];
			c++;
		}
		i++;
	}
	p[c] = '\0';
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
