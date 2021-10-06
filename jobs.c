#include "jobs.h"

// if check = 0 : both s and r
// if check < 0 : only s
// if check > 0 : only r

void jobs(int check)
{

    int job_number = 0;
    if (check == 0)
    {
        for (int i = 0; i < INT_MAX; i++)
        {
            if (process_arr[i].pid != -1)
            {
                char status[10];
                char stat_address[INT_MAX];
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *fp = fopen(stat_address, "r");
                char arr1[INT_MAX], arr2[INT_MAX], arr3[INT_MAX] = "";
                fscanf(fp, "%s %s %s", arr1, arr2, arr3);

                if (strcmp(arr3, "T") == 0)
                {
                    strcpy(status, "Stopped");
                }
                else
                {
                    strcpy(status, "Running");
                }

                job_number++;
                fclose(fp);
                printf("[%d] %s %s [%d]\n", job_number, status, process_arr[i].process_name, process_arr[i].pid);
            }
        }
    }
    else if (check < 0)
    {
        for (int i = 0; i < INT_MAX; i++)
        {
            if (process_arr[i].pid != -1)
            {
                char status[10];
                char stat_address[INT_MAX];
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *fp = fopen(stat_address, "r");
                char arr1[INT_MAX], arr2[INT_MAX], arr3[INT_MAX] = "";
                fscanf(fp, "%s %s %s", arr1, arr2, arr3);
                job_number++;
                if (strcmp(arr3, "T") == 0)
                {
                    strcpy(status, "Stopped");
                    printf("[%d] %s %s [%d]\n", job_number, status, process_arr[i].process_name, process_arr[i].pid);
                }

                fclose(fp);
            }
        }
    }
    else
    {
        for (int i = 0; i < INT_MAX; i++)
        {
            if (process_arr[i].pid != -1)
            {
                char status[10];
                char stat_address[INT_MAX];
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *fp = fopen(stat_address, "r");
                char arr1[INT_MAX], arr2[INT_MAX], arr3[INT_MAX] = "";
                fscanf(fp, "%s %s %s", arr1, arr2, arr3);
                job_number++;
                if (strcmp(arr3, "T") == 0)
                {
                }
                else
                {
                    strcpy(status, "Running");
                    printf("[%d] %s %s [%d]\n", job_number, status, process_arr[i].process_name, process_arr[i].pid);
                }

                fclose(fp);
            }
        }
    }
}