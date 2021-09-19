#include "pinfo.h"

void pinfo(pid_t pid, int pid_given)
{
    // If no pid entered
    if (pid_given == 0)
        pid = getpid();

    char arr1[INT_MAX], arr2[INT_MAX], arr3[INT_MAX] = "";

    /*========================================== For pid and Process Status  =====================================================================*/

    char address_string[INT_MAX];
    sprintf(address_string, "/proc/%d/stat", pid);

    FILE *fp = fopen(address_string, "r");

    if (fp == NULL)
    {
        printf("Process with pid %d not found\n", pid);
        return;
    }
    else
    {
        int if_foreground = 0;
        printf("pid -- %d\n", pid);

        fscanf(fp, "%s %s %s", arr1, arr2, arr3);
        char process_status[3];
        strcpy(process_status, arr3);

        if (pid == getpgid(pid))
        {
            if_foreground = 1;
        }
        if (if_foreground)
            strcat(process_status, "+");

        printf("Process Status -- %s\n", process_status);
    }
    fclose(fp);
    /*========================================== For Virtual Memory  =====================================================================*/

    strcpy(address_string, "");
    sprintf(address_string, "/proc/%d/statm", pid);

    fp = fopen(address_string, "r");
    fscanf(fp, "%s", arr1);

    char virtual_memory[100];
    strcpy(virtual_memory, arr1);
    printf("memory -- %s  {Virtual Memory}\n", virtual_memory);

    fclose(fp);
    /*========================================== For Executable Path  =====================================================================*/

    strcpy(address_string, "");
    sprintf(address_string, "/proc/%d/exe", pid);

    char *executable_path = (char *)malloc(INT_MAX * sizeof(char));
    for (int i = 0; i < INT_MAX; i++)
        executable_path[i] = '\0';

    readlink(address_string, executable_path, INT_MAX);

    printf("Executable Path -- %s\n", executable_path);
}