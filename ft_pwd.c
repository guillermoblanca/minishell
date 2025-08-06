#include "builtins.h"

void    print_pwd_error(t_shell *shell)
{
	write(STDERR_FILENO, "pwd:error", 9);
        write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 2);
        shell->g_status = 1;
}

void    ft_pwd(t_shell *shell)
{
        char    cwd[PATH_MAX];

        if (getcwd(cwd, PATH_MAX) == NULL)
                return (print_pwd_error(shell));
        write(shell->fdout, cwd, ft_strlen(cwd));
        write(shell->fdout, "\n", 2);
}
