#include "PreAllocString.h"
#include <stdio.h>
#include <cstring>

int main() {
    CREATE(pas, 7);
    PreAllocString& pas2 = pas;

    char res[] = "a\0";
    char rhs = res[0];
    pas=rhs;
    printf("pas: %s \n", pas.operator const char *());
    printf("pas2: %s \n", pas2.operator const char *());
    if(strcmp(pas.operator const char *(), &rhs) == 0) {
        printf("correct! \n");
    } else {
        printf("not correct");
    }
}