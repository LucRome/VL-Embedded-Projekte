#include "Printf.h"
#include <stdio.h>
#include "DestAppender.h"

int main() {
    // {
    //     //Allocate dst
    //     const int dst_length = 6;
    //     char dst[dst_length] = "abcde";
    //     printf("%c \n", dst[0]);
    //     DestAppender dstAppender = DestAppender(dst, dst + dst_length - 1);
    //     printf("%s\n", dst);
    //     char i = '0';
    //     while(dstAppender.appendCharToDest(i)) {
    //         printf("dst %c: %s\n", i, dst);
    //         i++;
    //     }
    //     dstAppender.resetDst();
    // }  

    {
        char dst[14] = {0};
        void* end = &dst[13];
        char fmt[] = "Hello %d";
        signed int arg = -12334;
        char result[] = "Hello -12334";
        
        Printf(dst, end, fmt, arg);
        printf("String: %s == %s \n", dst, result);
    }
}