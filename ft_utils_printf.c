/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:15:31 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/16 14:15:56 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_putunbr(unsigned int n)
{
	char	b;
	size_t	i;

	i = 0;
	if (n < 10)
	{
		b = n + 48;
		i += ft_putchar(b);
	}
	else
	{
		i += ft_putunbr(n / 10);
		i += ft_putunbr(n % 10);
	}
	return (i);
}

int	ft_putvoid(uintptr_t n)
{
	size_t	i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_puthexa(n, 'x');
	return (i);
}

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);

	// Calcular la longitud real del string
	s_len = 0;
	while (s[s_len])
		s_len++;

	// Si el inicio está fuera del string, devolvemos un string vacío
	if (start >= s_len)
		return (calloc(1, sizeof(char)));

	// Ajustar longitud si len es mayor que el resto del string
	if (len > s_len - start)
		len = s_len - start;

	// Reservar memoria
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);

	// Copiar caracteres
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';

	return (substr);
}
