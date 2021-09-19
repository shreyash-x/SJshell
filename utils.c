#include "utils.h"

void init_homedir()
{
    system("clear");
    getcwd(home_path, INT_MAX);
}