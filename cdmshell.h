#ifndef STRUCTURESCDMANDSHELL_H
# define STRUCTURESCDANDMSHELL_H

typedef struct s_cmd
{
        char    *cmd;
        char    **args;
        char    **incmd;
        char    **outcmd;
}       t_cmd;


typedef struct s_shell
{
        int             exec_signal;
        int             exit;
        int             infd;
        int             nextinfd;
        int             outfd;
        int             g_status;
        int             infile;
        int             outfile;
        int             error_parse
        int             prev_fd;
        pid_t   pid;
        char    *oldpwd;
        char    *prompt_parse;
        char    *prompt;
        char    *cmd_path;
        char    **env;
        char    **full_cmd;
        char    **split_cmd;
        t_cmd   **cmds;
}                       t_shell;

#endif
