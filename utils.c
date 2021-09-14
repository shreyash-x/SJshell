#include "utils.h"

void init_homedir()
{
    getcwd(home_path, INT_MAX);
}