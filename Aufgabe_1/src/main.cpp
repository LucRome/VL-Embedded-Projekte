#include "OptParser.h"
#include <string>

int main()
{
    //Parameter list
    char arg0[] = "ProgName";
    char arg1[] = "-x";
    char arg2[] = "-y=as";
    char arg3[] = "-k";

    char* argv[] = {arg0, arg1, arg2, arg3};

    int argc = sizeof(argv)/sizeof(argv[0]);

    CmdLineOptParser cmdP = CmdLineOptParser();
    cmdP.Parse(argc, argv);
}