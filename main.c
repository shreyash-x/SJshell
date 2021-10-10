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
#include "pipe.h"
#include "jobs.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "signal_handler.h"
#include "replay.h"
#include "execute.h"

int main()
{
    init_shell();

    while (1)
    {
        char *input_string = NULL;

        // Generating Prompt
        get_prompt();

        // Taking Input
        size_t n = 0;
        int ifcontrolD = getline(&input_string, &n, stdin);
        if (ifcontrolD == -1)
        {
            printf("\n");
            return 0;
        }
        input_string[strlen(input_string) - 1] = '\0';

        // Extracting commands from input string
        char commands[100][INT_MAX];
        int num_cmds = 0;
        char delim[2] = ";";
        char *cmd;
        char *sptr = input_string;
        while ((cmd = strtok_r(sptr, delim, &sptr)))
        {
            strcpy(commands[num_cmds], cmd);
            num_cmds++;
        }

        for (int i = 0; i < num_cmds; i++)
        {
            // Tokenizing command

            char input_tokens[100][INT_MAX];
            int itr = 0;
            char delimiter[5] = " \t";
            char *token;
            char temp[INT_MAX];
            strcpy(temp, commands[i]);
            char *sptr2 = commands[i];
            while ((token = strtok_r(sptr2, delimiter, &sptr2)))
            {
                strcpy(input_tokens[itr], token);
                itr++;
            }
            strcpy(commands[i], temp);

            execute2(input_tokens, itr, commands[i]);
        }
    }
}