#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <errno.h>

#include "job_control.h"

static pid_t shell_pgid = -1;


/*
 * =========================================================
 * JOB CONTROL INITIALIZATION
 * =========================================================
 */

void job_control_init(void)
{
    pid_t pid;

    /*
     * Job control only works with an interactive terminal.
     */

    if (!isatty(STDIN_FILENO))
    {
        return;
    }

    pid = getpid();

    /*
     * Ignore terminal job-control signals in the shell.
     */

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    /*
     * Put the shell into its own process group.
     */

    shell_pgid = pid;

    if (setpgid(shell_pgid, shell_pgid) < 0)
    {
        if (errno != EACCES && errno != EPERM)
        {
            perror("shellforge: setpgid");
        }
    }

    /*
     * Give the terminal to the shell.
     */

    if (tcsetpgrp(STDIN_FILENO, shell_pgid) < 0)
    {
        perror("shellforge: tcsetpgrp");
    }
}


/*
 * =========================================================
 * GIVE TERMINAL TO JOB
 * =========================================================
 */

void give_terminal_to(pid_t pgid)
{
    if (!isatty(STDIN_FILENO))
    {
        return;
    }

    if (tcsetpgrp(STDIN_FILENO, pgid) < 0)
    {
        perror("shellforge: give terminal");
    }
}


/*
 * =========================================================
 * TAKE TERMINAL BACK
 * =========================================================
 */

void take_terminal_back(void)
{
    if (!isatty(STDIN_FILENO))
    {
        return;
    }

    if (shell_pgid <= 0)
    {
        return;
    }

    if (tcsetpgrp(STDIN_FILENO, shell_pgid) < 0)
    {
        perror("shellforge: take terminal");
    }
}


/*
 * =========================================================
 * GET SHELL PROCESS GROUP
 * =========================================================
 */

pid_t get_shell_pgid(void)
{
    return shell_pgid;
}
