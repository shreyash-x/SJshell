#include "process.h"

void create_process_background(char input_tokens[][INT_MAX], char command[], int size)
{
    // for handling passing char* const* type input tokens in execvp
    char **temp_arr = (char **)malloc(INT_MAX * sizeof(char *));
    int arr_size = 0;
    for (int i = 0; i < size; i++)
    {
        temp_arr[i] = input_tokens[i];
        arr_size++;
    }
    // for (int i = 0; i < size; i++)
    //     printf("%s\n", temp_arr[i]);

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror(input_tokens[0]);
    }
    else if (pid == 0)
    {
        // Setting the process group ID
        setpgid(0, 0);

        if (execvp(temp_arr[0], temp_arr) == -1)
        {
            printf("%s: Command not found\n", temp_arr[0]);
            exit(EXIT_FAILURE);
        }
    }
    else // pid > 0
    {
        // reset fds
        dup2(default_input_FD, STDIN_FILENO);
        dup2(default_output_FD, STDOUT_FILENO);

        setpgid(pid, pid);

        strcpy(process_arr[process_size].process_name, command);
        process_arr[process_size].pid = pid;
        process_size++;
        sort_process_arr();

        printf("%d\n", pid);
    }
}
void create_process_foreground(char input_tokens[][INT_MAX], char command[], int size)
{
    // for handling passing char* const* type input tokens in execvp
    char **temp_arr2 = (char **)malloc(INT_MAX * sizeof(char *));
    int arr_size = 0;
    for (int i = 0; i < size; i++)
    {
        temp_arr2[i] = input_tokens[i];
        arr_size++;
    }

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror(input_tokens[0]);
    }
    else if (pid == 0)
    {
        // Setting the process group ID
        setpgid(0, 0);

        if (execvp(input_tokens[0], temp_arr2) == -1)
        {
            printf("%s: Command not found\n", input_tokens[0]);
            exit(EXIT_FAILURE);
        }
    }
    else // pid > 0
    {
        fg_process_pid = pid;
        // reset fds
        dup2(default_input_FD, STDIN_FILENO);
        dup2(default_output_FD, STDOUT_FILENO);

        // Process group id of the shell process
        pid_t cur_pgid = getpgid(getpid());
        // Ignoring Read Write signals. Prevents errors in tcsetgrp()
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        // Setting group pid of stdin and stdout
        tcsetpgrp(0, pid);
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
        fg_process_pid = -1;
        if (WIFSTOPPED(status))
        {
            strcpy(process_arr[process_size].process_name, command);
            process_arr[process_size].pid = pid;
            process_size++;
            sort_process_arr();
            // Sending stop signal to the child
            kill(pid, SIGSTOP);
        }
    }
}