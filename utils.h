#ifndef UTILS_H
# define UTILS_H

# include "stddef.h"
# include "stdlib.h"
# include "unistd.h"

int     ft_isalnum(int c);
int     ft_isdigit(int c);
char    *ft_strdup(const char *s1);
size_t  ft_strlcpy(char *dst, const char *src, size_t destsize);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlcat(char *dst, const char *src, size_t destsize);
size_t  ft_strlen(const char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_atoi(const char *str);
char    **ft_split(char const *s, char c);

#endif
