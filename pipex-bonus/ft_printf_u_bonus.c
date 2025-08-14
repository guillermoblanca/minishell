/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:43:05 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 13:18:44 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_putstr_b(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr_b("(null)"));
	while (s[i] != '\0')
	{
		ft_putchar_b(s[i]);
		i++;
	}
	return (i);
}

int	ft_putunbr_b(unsigned int n)
{
	char	b;
	size_t	i;

	i = 0;
	if (n < 10)
	{
		b = n + 48;
		i += ft_putchar_b(b);
	}
	else
	{
		i += ft_putunbr_b(n / 10);
		i += ft_putunbr_b(n % 10);
	}
	return (i);
}

int	ft_putvoid_b(uintptr_t n)
{
	size_t	i;

	i = 0;
	i += ft_putstr_b("0x");
	i += ft_puthexa_b(n, 'x');
	return (i);
}
