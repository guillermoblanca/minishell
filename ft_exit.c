#include "builtins.h"

void    ft_exit(char **command, t_shell *shell)
{
        shell->exit = 1;
        write(shell->outfd, "exit\n", 5);
        if (command[0] && command[1])
                print_exit_error(shell);
        else if (command[0] && ft_isdigit_str(command[0]) == 0)
                print_num_error(shell, command);
        else if (command[0])
                shell->g_status = ft_atoi(command[0]);
        else
                shell->g_status = 0;
}

void	print_exit_error(t_shell *shell)
{
	write(STDERR_FILENO, "exit: many arguments\n", 22);
	shell->g_status = 1;
}

void	print_num_error(t_shell *shell, char **command)
{
	write(STDERR_FILENO, "exit", 4);
	write(STDERR_FILENO, command[0], ft_strlen(command[0]));
	write(STDERR_FILENO, "num arg requiered", 17);
	shell->g_status = 1;
}
