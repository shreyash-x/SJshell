#ifndef __SJSUTILS__
#define __SJSUTILS__

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Global values
#define INT_MAX (int)1e4 + 9
char home_path[INT_MAX];
char prev_dir[INT_MAX];

// Functions
void init_homedir();

#endif