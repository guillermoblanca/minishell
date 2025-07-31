#include "stricturescdmandshell.h"

void    ft_exit(char **command, t_shell *shell)
{
        shell->exit = 1;
        write(shell->outfd, "exit\n", 5);
        if (command[0] && command[1])
                write_exit_toomany(shell);
        else if (command[0] && ft_isdigit_str(command[0]) == 0)
                write_numeric_err(shell, command);
        else if (command[0])
                shell->g_status = ft_atoi(command[0]);
        else
                shell->g_status = 0;
}

void	write_exit_toomany(t_shell *shell)
{
	write(STDERR_FILENO, "exit: too many arguments\n", 26);
	shell->g_status = 1;
}
