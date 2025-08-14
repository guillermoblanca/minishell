/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:26:28 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:20:53 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_substr_b(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	c;
	char	*p;

	i = 0;
	c = 0;
	if (start > ft_strlen_b(s))
		len = 0;
	else if (len > (ft_strlen_b(s) - start))
		len = ft_strlen_b(s) - start;
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

static size_t	ft_countwords(const char *s, const char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i++] != c && (s[i] == c || s[i] == '\0'))
			j++;
	}
	return (j);
}

static char	**free_all(char **str, int n)
{
	while (n > 0)
		free(str[--n]);
	free(str);
	return (0);
}

char	**ft_split_b(char const *s, char c)
{
	char	**str;
	size_t	len;
	size_t	n;

	str = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!str)
		return (0);
	n = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && (int)len++ > -1)
				s++;
			str[n] = ft_substr_b(s - len, 0, len);
			if (!str[n])
				return (free_all(str, n));
			n++;
		}
		else
			s++;
	}
	str[n] = NULL;
	return (str);
}
