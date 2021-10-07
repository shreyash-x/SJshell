#include "bg.h"

void exec_bg(int job_number)
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
                if (kill(process_arr[i].pid, SIGCONT) < 0)
                {
                    perror("");
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