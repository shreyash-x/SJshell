#include "sig.h"

void exec_sig(char input_tokens[][INT_MAX], int size)
{
    int job_number = atoi(input_tokens[1]);
    int signal_number = atoi(input_tokens[2]);

    if (size != 3)
    {
        fprintf(stderr, "Invalid number of arguments\n");
        return;
    }

    int jnum = 0;
    int found = 0;
    for (int i = 0; i < INT_MAX; i++)
    {
        if (process_arr[i].pid != -1)
        {
            jnum++;

            if (jnum == job_number)
            {
                if (kill(process_arr[i].pid, signal_number) < 0)
                {
                    perror("");
                }
                found = 1;
                break;
            }
        }
    }
    if (!found)
    {
        fprintf(stderr, "Please enter valid job number\n");
    }
}