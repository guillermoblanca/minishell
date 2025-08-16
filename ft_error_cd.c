void print_cd_error(t_shell *shell)
{
	write(STDERR_FILENO, "pwd: error", 10);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	shell->g_status = 1;
}

void print_backpwd_error(char *back, t_shell *shell)
{
	write(STDERR_FILENO, "cd: back pwd error", 18);
	write(STDERR_FILENO, back, ft_strlen(back));
	shell->g_status = 1;
}

void print_home_error(char *home, t_shell *shell)
{
	write(STDERR_FILENO, "no such file or directory", 25);
	write(STDERR_FILENO, home, ft_strlen(home));
	shell->g_status = 1;
}
void error_too_many_args(t_shell *shell)
{
	write(STDERR_FILENO, "cd: too many arguments", 22);
	shell->g_status = 1;
}

void cd_dash_error(t_shell *shell)
{
	write(STDERR_FILENO, "cd: dash error", 14);
	shell->g_status = 1;
}
