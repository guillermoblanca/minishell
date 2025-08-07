/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:16:42 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/16 14:16:50 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

int		ft_printf(const char *str, ...);
int		ft_convert(const char *c, va_list args, int i);
int		ft_putchar(char c);
int		ft_puthexa(unsigned long long n, char c);
int		ft_putnbr(int n);
int		ft_putstr(char *str);   
int		ft_putunbr(unsigned int n);
int		ft_putvoid(uintptr_t ptr);
char    *ft_substr(char const *s, unsigned int start, size_t len);
#endif
