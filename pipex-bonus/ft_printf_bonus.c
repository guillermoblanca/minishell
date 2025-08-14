/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:44:40 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 13:18:06 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_convert_b(const char *c, va_list args, int i)
{
	size_t	a;

	a = 0;
	if (c[i + 1] == 'c')
		a = ft_putchar_b(va_arg(args, int));
	else if (c[i + 1] == 's')
		a = ft_putstr_b(va_arg(args, char *));
	else if (c[i + 1] == 'p')
		a = ft_putvoid_b(va_arg(args, uintptr_t));
	else if (c[i + 1] == 'd' || c[i + 1] == 'i')
		a = ft_putnbr_b(va_arg(args, int));
	else if (c[i + 1] == 'u')
		a = ft_putunbr_b(va_arg(args, unsigned int));
	else if (c[i + 1] == 'x' || c[i + 1] == 'X')
		a = ft_puthexa_b(va_arg(args, unsigned int), c[i + 1]);
	else if (c[i + 1] == '%')
		a = ft_putchar_b('%');
	return (a);
}

int	ft_printf_b(const char *str, ...)
{
	va_list	elements;
	size_t	count;
	size_t	i;

	va_start (elements, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count = count + ft_convert_b(str, elements, i);
			i++;
		}
		else
			count += ft_putchar_b(str[i]);
		i++;
	}
	va_end (elements);
	return (count);
}

int	ft_putchar_b(char c)
{
	size_t	i;

	i = 0;
	write (1, &c, 1);
	i++;
	return (i);
}

int	ft_puthexa_b(unsigned long long n, char c)
{
	unsigned long long	i;

	i = 0;
	if (n >= 16)
		i += ft_puthexa_b(n / 16, c);
	if (c == 'x')
		ft_putchar_b("0123456789abcdef"[n % 16]);
	if (c == 'X')
		ft_putchar_b("0123456789ABCDEF"[n % 16]);
	i++;
	return (i);
}

int	ft_putnbr_b(int n)
{
	char	b;
	long	a;
	size_t	i;

	i = 0;
	a = (long) n;
	if (a < 0)
	{
		write (1, "-", 1);
		a = -a;
		i++;
	}
	if (a < 10)
	{
		b = a + 48;
		i += ft_putchar_b(b);
	}
	else
	{
		i += ft_putnbr_b(a / 10);
		i += ft_putnbr_b(a % 10);
	}
	return (i);
}
