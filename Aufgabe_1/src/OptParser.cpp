#include "OptParser.h"
#include <stdio.h>

bool CmdLineOptParser::Parse(int argc, char* argv[]) {
    
}

bool CmdLineOptParser::Option(const char c, const char* info) {
    //For Debugging: just print the content
    if(info == nullptr) {
        // no value
        printf("Variable: %c = TRUE");
    } else {
        printf("Variable: %c = %s", c, info);
    }
}