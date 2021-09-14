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
        char input_tokens[100][INT_MAX];
        size_t n = 0;

        // Generating Prompt
        get_prompt(home_path);

        // Taking Input
        getline(&input_string, &n, stdin);
        input_string[strlen(input_string) - 1] = '\0';

        // Tokenizing Input String
        int itr = 0;
        char delimiter[2] = " ";
        char *token;
        token = strtok(input_string, delimiter);
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