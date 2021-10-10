#include "replay.h"

pid_t pid = -1;

void kill_child(int sig)
{
    kill(pid, SIGTERM);
}

void replay(char command[], int interval, int period)
{
    char tokens[30][INT_MAX];
    int num_tokens = 0;
    char delim[5] = " \t";
    char *cmd;
    char *savepointer = command;
    while ((cmd = strtok_r(savepointer, delim, &savepointer)))
    {
        strcpy(tokens[num_tokens], cmd);
        num_tokens++;
    }

    // signal(SIGALRM, kill_child);
    // pid = fork();

    // if (pid < 0)
    // {
    //     perror(command);
    // }
    // else if (pid == 0)
    // {
    //     while (1)
    //     {
    //         sleep(interval);
    //         execute(tokens, num_tokens, command);
    //     }
    // }
    // else // pid > 0
    // {
    //     alarm(period);
    //     sleep(period);
    //     // kill(pid, SIGTERM);
    //     wait(NULL);
    // }

    int reps = period / interval;

    while (reps-- > 0)
    {
        sleep(interval);
        execute(tokens, num_tokens, command);
    }
    sleep(period % interval);
}

void exec_replay(char input_tokens[][INT_MAX], int size)
{
    char command[INT_MAX] = "";
    int interval, period, start, stop;

    for (int i = 1; i < size; i++)
    {
        if (strcmp(input_tokens[i], "-command") == 0)
        {
            start = i + 1;
            for (int j = i + 1; j < size; j++)
            {
                if (strcmp(input_tokens[j], "-interval") == 0 || strcmp(input_tokens[j], "-period") == 0)
                {
                    stop = j;
                    break;
                }
            }
        }
        else if (strcmp(input_tokens[i], "-interval") == 0)
        {
            interval = atoi(input_tokens[i + 1]);
        }
        else if (strcmp(input_tokens[i], "-period") == 0)
        {
            period = atoi(input_tokens[i + 1]);
        }
    }

    for (int i = start; i < stop - 1; i++)
    {
        strcat(command, input_tokens[i]);
        strcat(command, " ");
    }
    strcat(command, input_tokens[stop - 1]);

    // printf("%s %d %d\n", command, interval, period);
    replay(command, interval, period);
}
