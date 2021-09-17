#include "pinfo.h"

void pinfo(pid_t pid, int pid_given)
{
    // If no pid entered
    if (pid_given == 0)
        pid = getpid();
}