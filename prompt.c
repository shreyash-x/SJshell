#include "prompt.h"

void get_prompt(char *home_path)
{
    char host_name[INT_MAX], path[INT_MAX];
    char *env = getenv("LOGNAME");

    // Obtaining current working directory and host name
    getcwd(path, INT_MAX);
    gethostname(host_name, INT_MAX);

    // Assigning home_path as ~
    int s1 = strlen(home_path);
    int s2 = strlen(path);

    if (s2 >= s1)
    {
        path[0] = '~';
        int i;
        for (i = s1; i < s2; i++)
        {
            path[i + 1 - s1] = path[i];
        }
        path[i + 1 - s1] = '\0';
    }

    printf("<%s@%s:%s> ", env, host_name, path);
}