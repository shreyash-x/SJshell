#include "prompt.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"

int main()
{
    init_homedir();
    while (1)
    {
        char *input_string = NULL;

        // Generating Prompt
        get_prompt(home_path);

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
        }
    }
}