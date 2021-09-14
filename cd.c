#include "cd.h"

void goto_homedir()
{
    char temp[INT_MAX];
    getcwd(temp, INT_MAX);
    if (chdir(home_path) < 0)
    {
        perror("Error changing directory");
        return;
    }
    strcpy(prev_dir, temp);
}

void exec_cd(char *directory_path, int size)
{
    // Normal execution
    if (size == 2)
    {
        if (directory_path[0] == '-')
        {
            char temp[INT_MAX];
            getcwd(temp, INT_MAX);
            if (chdir(prev_dir) < 0)
            {
                printf("cd: %s: No such file or directory\n", directory_path);
                return;
            }
            printf("%s\n", prev_dir);
            strcpy(prev_dir, temp);
        }
        else if (strcmp(directory_path, "~") == 0)
        {
            goto_homedir();
        }
        else if (directory_path[0] != '/')
        {
            char cd_path[INT_MAX];
            char temp[INT_MAX];
            getcwd(temp, INT_MAX);
            getcwd(cd_path, INT_MAX);
            strcat(cd_path, "/");
            strcat(cd_path, directory_path);

            if (chdir(cd_path) < 0)
            {
                printf("cd: %s: No such file or directory\n", cd_path);
                return;
            }
            strcpy(prev_dir, temp);
        }
        else if (directory_path[0] == '/')
        {
            char temp[INT_MAX];
            getcwd(temp, INT_MAX);
            if (chdir(directory_path) < 0)
            {
                printf("cd: %s: No such file or directory\n", directory_path);
                return;
            }
            strcpy(prev_dir, temp);
        }
    }
    // Go to home directory
    else if (size == 1)
    {
        goto_homedir();
    }
    // Error
    else if (size > 2)
    {
        printf("cd: Too many arguments!\n");
        return;
    }
}