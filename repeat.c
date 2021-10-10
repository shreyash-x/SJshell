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
#include "execute.h"

void exec_repeat(char input_tokens[][INT_MAX], int itr, char command[])
{
    int repetitions = atoi(input_tokens[1]);
    for (int i = 2; i < itr; i++)
    {
        strcpy(input_tokens[i - 2], input_tokens[i]);
    }
    itr = itr - 2;

    // removing first two words from command
    int pos = 0, cnt = 0;
    for (int i = 0; command[i] != '\0'; i++)
    {
        if (command[i] == ' ')
            cnt++;

        if (cnt == 2)
        {
            pos = i;
            break;
        }
    }
    int k = 0;
    for (int i = pos + 1; command[i] != '\0'; i++, k++)
    {
        command[k] = command[i];
    }
    command[k] = '\0';

    while (repetitions-- > 0)
    {
        // printf("%d %s\n", itr, command);
        execute2(input_tokens, itr, command);
    }
}