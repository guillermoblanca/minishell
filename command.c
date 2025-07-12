#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "command.h"
static int g_last_exit_code = 0;

int get_last_exit_code()
{
    return g_last_exit_code;
}

void execute_pipeline(char **argv1, char **argv2)
{
    int fd[2];
    pipe(fd);

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(argv1[0], argv1);
        perror("execvp");
        _exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(argv2[0], argv2);
        perror("execvp");
        _exit(1);
    }

    // Padre
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void execute_command(char **argv, char *output_file, t_token_type redir_type)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo
        if (output_file != NULL)
        {
            int fd;
            if (redir_type == TOKEN_REDIR_OUT_APPEND)
                fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0)
            {
                perror("open");
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(argv[0], argv);
        exit(1);
    }

    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_last_exit_code = WEXITSTATUS(status);
        else
            g_last_exit_code = 1;
    }
    else
    {
        perror("fork");
        exit(1);
    }
}
