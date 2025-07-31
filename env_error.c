#include "structurescdmandshell.h"

void	error_env(char *command, int i)
{
	write(STDERR_FILENO, "not identifier", 22);
	while (command[i] != '\0' && command[i] != '=')
		write(STDERR_FILENO, &command[i++], 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error1_env(char *command, int i)
{
	write(STDERR_FILENO, "export: not valid", 17);
	while (command[i] != '\0' && command[i] != '=')
		write(STDERR_FILENO, &command[i++], 1);
	write(STDERR_FILENO, "\n", 1);
}

void	error2_env(char *command, int i)
{
	write(STDERR_FILENO, "export: ", 8);
	while (command[i] != '\0' && command[i] != '=')
		i++;
	i++;
	write(STDERR_FILENO, &command[i], 1);
	write(STDERR_FILENO, "not a valid identifier", 22);
}
void	env_err3(void)
{
	write(STDERR_FILENO, "export: not valid", 17);
	write(STDERR_FILENO, "\n", 2);
}

