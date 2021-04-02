#include "Printf.h"
#include <stdio.h>

int main() {
    char* ret = Printf(nullptr, nullptr, nullptr, 'a');
    if(!ret) {
        printf("null");
    } else {
        printf(ret);
    }
}