#include "signal_handler.h"

void controlZ(int sig)
{
    pid_t pgid = getpgid(fg_process_pid);

    // printf("%d %d %d\n", shellpid, pgid, fg_process_pid);
    printf("\n");
    if (shellpgid != pgid)
    {
        kill(fg_process_pid, SIGTSTP);
        // printf("Done\n");
    }
    else
    {
        // printf("Done2\n");
        get_prompt();
    }
    fflush(stdout);
}

void controlC(int sig)
{
    pid_t pgid = getpgid(fg_process_pid);

    // printf("%d %d %d\n", shellpid, pgid, fg_process_pid);
    printf("\n");
    if (shellpgid != pgid)
    {
        kill(fg_process_pid, SIGINT);
        // printf("Done\n");
    }
    else
    {
        // printf("Done2\n");
        get_prompt();
    }
    fflush(stdout);
}
