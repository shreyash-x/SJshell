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

// Global values
#define INT_MAX (int)1e3 + 9
char home_path[INT_MAX];
char prev_dir[INT_MAX];

// Functions
void init_homedir();

#endif