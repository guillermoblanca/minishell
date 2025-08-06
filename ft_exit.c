#include "builtins.h"

void    ft_exit(char **cmd, t_shell *shell)
{
        shell->exit = 1;
        write(shell->outfd, "exit\n", 5);
        if (cmd[0] && cmd[1])
                print_exit_error(shell);
        else if (cmd[0] && ft_isdigit_str(cmd[0]) == 0)
                print_num_error(shell, cmd);
        else if (command[0])
                shell->g_status = ft_atoi(cmd[0]);
        else
                shell->g_status = 0;
}

void	print_exit_error(t_shell *shell)
{
	write(STDERR_FILENO, "exit: many arguments\n", 22);
	shell->g_status = 1;
}

void	print_num_error(t_shell *shell, char **cmd)
{
	write(STDERR_FILENO, "exit", 4);
	write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
	write(STDERR_FILENO, "requiered: num arg", 18);
	shell->g_status = 1;
}
