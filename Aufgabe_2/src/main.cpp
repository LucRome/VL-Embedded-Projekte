#include "Printf.h"
#include <stdio.h>
#include "DestAppender.h"

int main() {
    char dst[20] = {0};
    char* end = dst + sizeof(dst);

    // Wrong type of argument
    char fmt[] = "%d, %u, %s, %s";
    int arg = -124;
    unsigned int arg2 = 32;
    int arg3 = 0xFF;

    //char res[] = "-124, 32, FF, "; // Wrong type: interpreted as the needed Type -> evtl error
    
    char* ret = Printf(dst, end, fmt, arg, arg2, arg3);
    printf("dst: %s, ret: %s", dst, ret);    
}