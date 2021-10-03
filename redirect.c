#include "redirect.h"

void input_redirection(char input_tokens[][INT_MAX], int pos)
{
    char fileName[INT_MAX];
    strcpy(fileName, input_tokens[pos + 1]);
    int input_FD = open(fileName, O_RDONLY);
    if (input_FD < 0)
    {
        perror("Error opening the file");
        return;
    }
    else
    {
        dup2(input_FD, STDIN_FILENO);
        close(input_FD);
    }
}
void output_redirection(char input_tokens[][INT_MAX], int pos)
{
    char isAppend = 0;
    char fileName[INT_MAX];
    strcpy(fileName, input_tokens[pos + 1]);

    // Checking for append mode
    if (strcmp(input_tokens[pos], ">>") == 0)
        isAppend = 1;

    int output_FD;

    if (isAppend)
    {
        output_FD = open(fileName, O_APPEND | O_WRONLY | O_CREAT, 0644);
    }
    else
    {
        output_FD = open(fileName, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    }

    if (output_FD < 0)
    {
        perror("Error opening the file");
        return;
    }
    else
    {
        dup2(output_FD, STDOUT_FILENO);
        close(output_FD);
    }
}

int check_redirection(char input_tokens[][INT_MAX], int size)
{
    int pos_input_sign, pos_output_sign;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(input_tokens[i], "<") == 0)
        {
            pos_input_sign = i;
            input_redirection(input_tokens, pos_input_sign);
            count++;
        }
        if (strcmp(input_tokens[i], ">") == 0 || strcmp(input_tokens[i], ">>") == 0)
        {
            pos_output_sign = i;
            output_redirection(input_tokens, pos_output_sign);
            count++;
        }
    }
    size -= count * 2;
    return size;
}
