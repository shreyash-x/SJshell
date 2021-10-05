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

    while (repetitions-- > 0)
    {
        execute(input_tokens, itr, command);
    }
}