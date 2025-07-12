#include <unistd.h>
#include "printf.h"

void printText(const char **str)
{
    while (str)
    {
        write(0,&str,1);
        str++;
    }
}