#include "fg.h"

void exec_fg(int job_number, char command[])
{
    int jnum = 0;
    int found = 0;
    for (int i = 0; i < INT_MAX; i++)
    {
        if (process_arr[i].pid != -1)
        {
            jnum++;
            if (job_number == jnum)
            {
                found = 1;
                pid_t pid = process_arr[i].pid;
                // Process group id of the shell process
                pid_t cur_pgid = getpgid(getpid());
                // Ignoring Read Write signals. Prevents errors in tcsetgrp()
                signal(SIGTTOU, SIG_IGN);
                signal(SIGTTIN, SIG_IGN);
                // Setting group pid of stdin and stdout
                tcsetpgrp(0, getpgid(pid));
                if (kill(pid, SIGCONT) < 0)
                {
                    perror("");
                }
                // tcsetpgrp(1, pid);
                // Get status for stopped children
                int status;
                waitpid(pid, &status, WUNTRACED);
                // Re setting process group id of stdin and stdout
                tcsetpgrp(0, cur_pgid);
                // tcsetpgrp(1, cur_pgid);
                // Resetting the signals to default
                signal(SIGTTOU, SIG_DFL);
                signal(SIGTTIN, SIG_DFL);

                if (WIFSTOPPED(status))
                {
                    strcpy(process_arr[process_size].process_name, command);
                    process_arr[process_size].pid = pid;
                    process_size++;

                    // Sending stop signal to the child
                    kill(pid, SIGSTOP);
                }

                break;
            }
        }
    }

    if (!found)
    {
        fprintf(stderr, "Please enter valid job number\n");
    }
}