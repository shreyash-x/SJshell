#ifndef __SJSUTILS__
#define __SJSUTILS__

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Global values
#define INT_MAX 1009
char home_path[INT_MAX];
char prev_dir[INT_MAX];
int process_size;
int default_input_FD;
int default_output_FD;
pid_t shellpid, shellpgid;
pid_t fg_process_pid;

// Data Structures
typedef struct process_info process_info;
struct process_info
{
    char process_name[INT_MAX];
    pid_t pid;
};
process_info process_arr[INT_MAX];

// Functions
void init_shell();

#endif