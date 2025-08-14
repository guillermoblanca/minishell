/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:38:02 by leiamart          #+#    #+#             */
/*   Updated: 2024/12/06 19:49:08 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_countwords(const char *s, const char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i++] != c && (s[i] == c || s[i] == '\0'))
			n++;
	}
	return (n);
}

static char	**free_all(char **str, int n)
{
	while (n > 0)
		free(str[--n]);
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
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
			str[n] = ft_substr(s - len, 0, len);
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
