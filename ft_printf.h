#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

int             ft_putstr(char *s);
int             ft_putunbr(unsigned int n);
int             ft_putvoid(uintptr_t n);
int             ft_putchar(char c);
int             ft_puthexa(unsigned long long n, char c);
int             ft_putnbr(int n);
int             ft_convert(const char *c, va_list args, int i);
int             ft_printf(const char *str, ...);

#endif
