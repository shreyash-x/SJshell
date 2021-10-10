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
                char stat_address[100];
                // printf("{{%d}}", process_arr[i].pid);
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *f1 = fopen(stat_address, "r");
                char arr1[100], arr2[100], arr3[100] = "";
                fscanf(f1, "%s %s %s", arr1, arr2, arr3);

                if (strcmp(arr3, "T") == 0)
                {
                    strcpy(status, "Stopped");
                }
                else
                {
                    strcpy(status, "Running");
                }

                job_number++;
                printf("[%d] %s %s [%d]\n", job_number, status, process_arr[i].process_name, process_arr[i].pid);
                fclose(f1);
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
                char stat_address[100];
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *fp = fopen(stat_address, "r");
                char arr1[100], arr2[100], arr3[100] = "";
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
                char stat_address[100];
                sprintf(stat_address, "/proc/%d/stat", process_arr[i].pid);

                FILE *fp = fopen(stat_address, "r");
                char arr1[100], arr2[100], arr3[100] = "";
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
