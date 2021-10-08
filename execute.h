#ifndef _EXEC_SH
#define _EXEC_SH

#include "utils.h"
#include "prompt.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "process.h"
#include "trackbg.h"
#include "repeat.h"
#include "pinfo.h"
#include "redirect.h"
#include "jobs.h"
#include "pipe.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
void execute(char input_tokens[][INT_MAX], int itr, char command[]);

#endif