#include <unistd.h>
#include "printstring.h"

void print_str(const char **str)
{
    while (str != nullptr)
    {
        write(0,&str, 1);
        str++;
    }
}