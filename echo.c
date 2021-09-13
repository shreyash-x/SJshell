#include "echo.h"

void get_echo(char input_tokens[][INT_MAX], int size)
{
    for (int i = 1; i < size; i++)
    {
        printf("%s", input_tokens[i]);
    }
    printf("\n");
}