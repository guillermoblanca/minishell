/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:07:17 by leiamart          #+#    #+#             */
/*   Updated: 2024/11/30 18:26:58 by leiamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

typedef struct s_command
{
	char				**cmd;
	struct s_command	*next;
}	t_command;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_arg
{
	t_list		*cmd;
	t_list		*cmdpath;
	t_command	*command;
	t_list		*firstcmd;
	t_list		*firstpath;
	t_command	*firstcommand;
	char		*limit;
	char		*file1;
	char		*file2;
	int			fd1;
	int			fd2;
	int			cmd_n;
	int			index;
	int			heredocflag;
}	t_arg;

void		ft_child_bonus(t_arg *a, char **e);
void		ft_child_cmd_bonus(t_arg *a, int pfd[2], char **e);
void		ft_error_bonus(t_arg *a, char *e);
t_command	*ft_new_cmd(char *c);

void		ft_add_back(t_command **l, t_command *n);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);

void		ft_clear_list(t_list **a);
void		ft_path_free(t_arg *a);
void		*ft_free_b(char **str, int c);
void		*ft_free_arg_bonus(t_arg *a);

void		ft_infile_b(t_arg *a);
void		ft_outfile_heredoc(t_arg *a);
void		ft_outfile_b(t_arg *a);

void		ft_initialize_bn(t_arg *a);
void		ft_heredoc_init(t_arg *a, char **argv, int argc);
void		ft_heredoc(t_arg *a, char **argv, int argc);

void		ft_error_arg_b(t_arg *a, t_list *aux);
char		*ft_cmd_bonus(char *e, char *c);
void		ft_files_bonus(t_arg *a);
void		ft_start_arg(t_arg *a, char **argv, int argc);
t_arg		ft_args_b(t_arg *a, char **e);

int			ft_strncmp_b(const char *s1, const char *s2, size_t n);
size_t		ft_strlen_b(const char *s);
char		*ft_strjoin_b(char const *s1, char const *s2);
size_t		ft_strlcat_b(char *dst, const char *src, size_t destsize);
int			ft_strcmp(const char *s1, const char *s2);

char		*ft_freegnl(char **str);
char		*ft_line(char *buffer, char **l);
char		*ft_readfile(int fd, char *r);
char		*get_next_line_p(int fd);
ssize_t		ft_strlen_gnl(char *str);
char		*ft_strchr_gnl(char *str, int c);
char		*ft_substr_gnl(char *str, unsigned int start, ssize_t len);
char		*ft_strdup_gnl(char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);

char		**ft_split_b(char const *s, char c);
char		*ft_substr_b(char const *s, unsigned int start, size_t len);

int			ft_convert_b(const char *c, va_list args, int i);
int			ft_printf_b(const char *str, ...);
int			ft_putchar_b(char c);
int			ft_puthexa_b(unsigned long long n, char c);
int			ft_putnbr_b(int n);
int			ft_putstr_b(char *s);
int			ft_putunbr_b(unsigned int n);
int			ft_putvoid_b(uintptr_t n);

#endif
