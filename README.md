# SJshell
 
 This is a basic implementation of a shell written in c as part of the Operating Systems Assignment-2 with built in functionalities like cd, ls, pwd, repeat and pinfo.
 

 ## Usage
---
 1. `make`
 2. `./sjs`

 ## Files
---
 ### cd.c
 - This file consists of the implementation of the cd command.
 ### execute.c
 - This file checks the given input and calls the required functions as per the input.
 ### echo.c
 - This file consists of the implementation of the echo command.
 - This echo command ignores extra spaces
 ### ls.c
 - This file consists of the implementation of the ls command.
 - For files with date of creation >= 6 months, its year of creation has been printed instead of time in `ls -l` mode.
 ### main.c
 - Takes the input, tokenizes them separating by ';' and whitespaces ' '
 - Checks the input command and calls the desired function
 ### pinfo.c
 - This file consists of the implementation of pinfo command
 - This prints the process-related info : pid, Process Status, Virtual Memory and Executable Path
 ### process.c
 - This file provides the functionality to create foreground and background processes.
 - This enables the execution of System commands.
 ### prompt.c
 - This generates the prompt of the shell.
 ### pwd.c
 - This file consists of the implementation of the pwd command.
 ### repeat.c
 - This file consists of the implementation of the repeat command.
 - `repeat n <command>` executes the command n times.
 ### trackbg.c
 - This file tracks when a background process exits and displays its message on the shell.
 ### redirect.c
 - This file provides the functionality of input output redirection.
 ### pipe.c
 - This file enables piping functionality in c.
 ### jobs.c
 - This file consists of the implementation of the jobs command.
 ### sig.c
 - This file consists of the implementation of the sig command.
 ### signal_handler.c
 - This file handles Ctrl+C and Ctrl+Z signals.
 ### fg.c
 - This file consists of the implementation of the fg command.
 ### bg.c
 - This file consists of the implementation of the bg command.
 ### replay
 - This file consists of the implementation of the replay command.
 ### utils.c and utils.h
 - This file consists of the header files, global variables and also a function to initiate the shell.
