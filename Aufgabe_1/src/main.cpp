#include "OptParser.h"
#include <string>
#include <stdio.h>

int main()
{
    //Parameter list
    char arg0[] = "ProgName";
    char arg1[] = "-x";
    char arg2[] = "-y=as";
    char arg3[] = "-k";
    // char arg4[] = "hello";

    printf("Controll: %s %s %s %s\n", arg0, arg1, arg2, arg3);

    char* argv[] = {arg0, arg1, arg2, arg3};

    int argc = sizeof(argv)/sizeof(argv[0]);
    printf("argc: %i\n", argc);

    CmdLineOptParser cmdP = CmdLineOptParser();
    
    if (cmdP.Parse(argc, argv)) {
        printf("success \n");
    } else {
        printf("error \n");
    }
}