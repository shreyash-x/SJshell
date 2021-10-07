#include "utils.h"
#include "trackbg.h"

void init_shell()
{
    getcwd(home_path, INT_MAX);

    process_size = 0;
    for (int i = 0; i < INT_MAX; i++)
    {
        process_arr[i].pid = -1;
    }
    signal(SIGCHLD, background_process_signal);

    default_input_FD = dup(STDIN_FILENO);
    default_output_FD = dup(STDOUT_FILENO);
}