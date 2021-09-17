#ifndef _PROC_SH
#define _PROC_SH

#include "utils.h"
void create_process_background(char input_tokens[][INT_MAX], char command[INT_MAX], int size);
void create_process_foreground(char input_tokens[][INT_MAX], char command[INT_MAX], int size);

#endif