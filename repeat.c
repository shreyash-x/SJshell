#include "repeat.h"
#include "prompt.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "process.h"
#include "trackbg.h"
#include "repeat.h"
#include "pinfo.h"
#include "redirect.h"

void exec_repeat(char input_tokens[][INT_MAX], int itr, char command[])
{
    int repetitions = atoi(input_tokens[1]);
    for (int i = 2; i < itr; i++)
    {
        strcpy(input_tokens[i - 2], input_tokens[i]);
    }
    itr = itr - 2;

    while (repetitions-- > 0)
    {
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
        else if (strcmp(input_tokens[0], "pinfo") == 0)
        {
            if (itr == 1)
                pinfo(0, 0);
            else
                pinfo(atoi(input_tokens[1]), 1);
        }
        else
        {
            // Foreground Process
            create_process_foreground(input_tokens, command, itr);
        }
    }
}