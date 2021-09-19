#include "prompt.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "process.h"
#include "trackbg.h"
#include "repeat.h"
#include "pinfo.h"

int main()
{
    init_homedir();
    process_size = 0;
    for (int i = 0; i < INT_MAX; i++)
    {
        process_arr[i].pid = -1;
    }
    signal(SIGCHLD, background_process_signal);

    while (1)
    {
        char *input_string = NULL;

        // Generating Prompt
        get_prompt();

        // Taking Input
        size_t n = 0;
        getline(&input_string, &n, stdin);
        input_string[strlen(input_string) - 1] = '\0';

        // Extracting commands from input string
        char commands[100][INT_MAX];
        int num_cmds = 0;
        char delim[2] = ";";
        char *cmd;
        cmd = strtok(input_string, delim);
        while (cmd != NULL)
        {
            strcpy(commands[num_cmds], cmd);
            num_cmds++;
            cmd = strtok(NULL, delim);
        }

        for (int i = 0; i < num_cmds; i++)
        {
            // Tokenizing command
            char input_tokens[100][INT_MAX];
            int itr = 0;
            char delimiter[2] = " ";
            char *token;
            token = strtok(commands[i], delimiter);
            while (token != NULL)
            {
                strcpy(input_tokens[itr], token);
                itr++;
                token = strtok(NULL, delimiter);
            }
            if (strcmp(input_tokens[0], "repeat") == 0)
            {
                exec_repeat(input_tokens, itr, commands[i]);
            }
            else if (strcmp(input_tokens[0], "echo") == 0)
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
            else if (strcmp(input_tokens[0], "pinfo") == 0)
            {
                if (itr == 1)
                    pinfo(0, 0);
                else
                    pinfo(atoi(input_tokens[1]), 1);
            }
            else if (strcmp(input_tokens[itr - 1], "&") == 0)
            {
                // Background Process
                itr--;
                create_process_background(input_tokens, commands[i], itr);
            }
            else
            {
                // printf("%s %ld\n",input_tokens[itr-1],strlen(input_tokens[itr-1]));
                // Foreground Process
                create_process_foreground(input_tokens, commands[i], itr);
            }
        }
    }
}