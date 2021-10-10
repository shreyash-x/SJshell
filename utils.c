#include "utils.h"
#include "trackbg.h"
#include "signal_handler.h"

void init_shell()
{
    getcwd(home_path, INT_MAX);

    shellpid = getpid();
    shellpgid = getpgid(shellpid);

    process_size = 0;
    for (int i = 0; i < INT_MAX; i++)
    {
        process_arr[i].pid = -1;
        strcpy(process_arr[i].process_name, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    }
    signal(SIGCHLD, background_process_signal);
    signal(SIGTSTP, controlZ);
    signal(SIGINT, controlC);

    default_input_FD = dup(STDIN_FILENO);
    default_output_FD = dup(STDOUT_FILENO);
}

void swap(int a, int b)
{
    pid_t temp = process_arr[a].pid;
    process_arr[a].pid = process_arr[b].pid;
    process_arr[b].pid = temp;

    char temp_name[INT_MAX];
    strcpy(temp_name, process_arr[a].process_name);
    strcpy(process_arr[a].process_name, process_arr[b].process_name);
    strcpy(process_arr[b].process_name, temp_name);
}

void sort_process_arr()
{
    for (int i = 0; i < INT_MAX; i++)
    {
        for (int j = i + 1; j < INT_MAX; j++)
        {
            if (process_arr[i].pid != -1 && process_arr[j].pid != -1)
            {
                if (strcmp(process_arr[i].process_name, process_arr[j].process_name) > 0)
                {
                    swap(i, j);
                }
            }
        }
    }
}