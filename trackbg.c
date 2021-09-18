#include "trackbg.h"
#include "prompt.h"

void background_process_signal(int signal)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0)
    {
        for (int i = 0; i < process_size; i++)
        {
            if (process_arr[i].pid == pid)
            {
                char *p_name = process_arr[i].process_name;
                if (status == 0)
                {
                    fprintf(stderr, "\n%s with pid %d exited normally\n", p_name, pid);
                }
                else
                {
                    fprintf(stderr, "\n%s with pid %d exited abnormally\n", p_name, pid);
                }
                process_arr[i].pid = -1;
                get_prompt();
                fflush(stdout);
            }
        }
    }
}