/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:07:17 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 17:53:07 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"
# include "string.h"
# include "stdint.h"
# include "stdarg.h"
# include "errno.h"
# include "sys/wait.h"
# include "ctype.h"

typedef struct s_args
{
	char	*cmd1;
	char	*cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**command1;
	char	**command2;
	char	*file1;
	char	*file2;
	int		fd1;
	int		fd2;
}	t_args;

void	ft_error(t_args *a, char *e);
void	ft_child(t_args *a, int pfd[2], char **c);
void	ft_infile(t_args *a);
void	ft_outfile(t_args *a);

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t destsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_putstr(char *s);
int		ft_putunbr(unsigned int n);
int		ft_putvoid(uintptr_t n);
int		ft_putchar(char c);
int		ft_puthexa(unsigned long long n, char c);
int		ft_putnbr(int n);
int		ft_convert(const char *c, va_list args, int i);
int		ft_printf(const char *str, ...);

void	ft_files(t_args *a);
char	*ft_command(char *c, char *e);
t_args	ft_arg(t_args *a, char **e);

void	*ft_free(char **str, int c);
void	ft_free_matrix(char **str);
void	ft_free_cmd(t_args *a);
void	*ft_free_arg(t_args *a);

void	ft_initialize(t_args *a);
void	ft_parse_arg(t_args *a, char **argv);

#endif
