#include "Printf.h"
#include "DestAppender.h"

int main()
{
    char dst[20] = {0};
    char *end = dst + sizeof(dst);

    // Wrong type of argument
    char fmt[] = "%d, %u, %s, %s";
    int arg = -124;
    unsigned int arg2 = 32;
    char arg3 = '\0';
    char arg4 = '\0';

    //char res[] = "-124, 32, FF, "; // Wrong type: interpreted as the needed Type -> evtl error

    Printf(dst, end, fmt, arg, arg2, arg3, arg4);
}