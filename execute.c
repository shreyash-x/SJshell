#include "execute.h"

void execute(char input_tokens[][INT_MAX], int itr, char command[])
{

    int hasPipe = 0;
    for (int j = 0; j < itr; j++)
    {
        if (strcmp(input_tokens[j], "|") == 0)
        {
            hasPipe = 1;
            break;
        }
    }

    if (hasPipe)
    {
        exec_pipe(input_tokens, itr, command);
        return;
    }

    itr = check_redirection(input_tokens, itr);

    if (strcmp(input_tokens[0], "echo") == 0)
    {
        get_echo(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "pwd") == 0)
    {
        get_pwd();
    }
    else if (strcmp(input_tokens[0], "cd") == 0)
    {
        exec_cd(input_tokens[1], itr);
    }
    else if (strcmp(input_tokens[0], "ls") == 0)
    {
        exec_ls(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "sig") == 0)
    {
        exec_sig(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "fg") == 0)
    {
        exec_fg(atoi(input_tokens[1]), command);
    }
    else if (strcmp(input_tokens[0], "bg") == 0)
    {
        exec_bg(atoi(input_tokens[1]));
    }
    else if (strcmp(input_tokens[0], "replay") == 0)
    {
        exec_replay(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "pinfo") == 0)
    {
        if (itr == 1)
            pinfo(0, 0);
        else
            pinfo(atoi(input_tokens[1]), 1);
    }
    else if (strcmp(input_tokens[0], "jobs") == 0)
    {
        int check = 0;
        if (itr > 1)
        {
            for (int k = 1; k < itr; k++)
            {
                if (strcmp(input_tokens[k], "-r") == 0)
                {
                    check = 1;
                }
                else if (strcmp(input_tokens[k], "-s") == 0)
                {
                    check = -1;
                }
            }
        }
        jobs(check);
    }
    else
    {
        // Foreground Process
        create_process_foreground(input_tokens, command, itr);
    }
    dup2(default_input_FD, STDIN_FILENO);
    dup2(default_output_FD, STDOUT_FILENO);
}

void execute2(char input_tokens[][INT_MAX], int itr, char command[])
{

    // printf("||%s||\n", command);

    if (strcmp(input_tokens[0], "repeat") == 0)
    {
        exec_repeat(input_tokens, itr, command);
        return;
    }

    int hasPipe = 0;
    for (int j = 0; j < itr; j++)
    {
        if (strcmp(input_tokens[j], "|") == 0)
        {
            hasPipe = 1;
            break;
        }
    }

    if (hasPipe)
    {
        exec_pipe(input_tokens, itr, command);
        return;
    }

    itr = check_redirection(input_tokens, itr);

    if (strcmp(input_tokens[0], "echo") == 0)
    {
        get_echo(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "pwd") == 0)
    {
        get_pwd();
    }
    else if (strcmp(input_tokens[0], "cd") == 0)
    {
        exec_cd(input_tokens[1], itr);
    }
    else if (strcmp(input_tokens[0], "ls") == 0)
    {
        exec_ls(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "sig") == 0)
    {
        exec_sig(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "fg") == 0)
    {
        exec_fg(atoi(input_tokens[1]), command);
    }
    else if (strcmp(input_tokens[0], "bg") == 0)
    {
        exec_bg(atoi(input_tokens[1]));
    }
    else if (strcmp(input_tokens[0], "replay") == 0)
    {
        exec_replay(input_tokens, itr);
    }
    else if (strcmp(input_tokens[0], "pinfo") == 0)
    {
        if (itr == 1)
            pinfo(0, 0);
        else
            pinfo(atoi(input_tokens[1]), 1);
    }
    else if (strcmp(input_tokens[0], "jobs") == 0)
    {
        int check = 0;
        if (itr > 1)
        {
            for (int k = 1; k < itr; k++)
            {
                if (strcmp(input_tokens[k], "-r") == 0)
                {
                    check = 1;
                }
                else if (strcmp(input_tokens[k], "-s") == 0)
                {
                    check = -1;
                }
            }
        }
        jobs(check);
    }
    else if (strcmp(input_tokens[itr - 1], "&") == 0)
    {
        // Background Process
        itr--;
        // for (int i = 0; command[i] != '\0'; i++)
        // {
        //     if (command[i] == '&')
        //         command[i] = '\0';
        // }
        create_process_background(input_tokens, command, itr);
    }
    else
    {
        // Foreground Process
        create_process_foreground(input_tokens, command, itr);
    }
    dup2(default_input_FD, STDIN_FILENO);
    dup2(default_output_FD, STDOUT_FILENO);
}
