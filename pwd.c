#include "pwd.h"

void get_pwd()
{
    char presentwd[INT_MAX];
    getcwd(presentwd, INT_MAX);

    printf("%s\n", presentwd);
}