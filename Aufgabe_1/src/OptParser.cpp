#include "OptParser.h"
#include "OptChecker.h"
#include <stdio.h>

bool CmdLineOptParser::Parse(int argc, char* argv[]) {

    //iterate over all arguments and check them
    //only while result is not false
    for(int i = 1; i < argc; i++) {
        printf("argv[%i]: %s \n", i, argv[i]);
        char varName = 0;
        char* ptr_value = nullptr;
        
        //must start with Variable
        if(argv[i] == nullptr || !CmdLineOptChecker::isVariable(argv[i])) {
            return false;
        } else {
            //+ 1: '-'x (argv[i] points to '-' and x is needed)
            int offset = 1;
            varName = *(argv[i] + offset);
            
            // get value
            offset = 2;
            if(!CmdLineOptChecker::EOA(argv[i] + offset)) {
                //-> Value or Equals
                
                if(CmdLineOptChecker::isEquals(argv[i] + offset)) {
                    offset++; //ignore Equals
                }

                if(!CmdLineOptChecker::isValue(argv[i] + offset)) {
                    return false;
                } else {
                    ptr_value = (argv[i] + offset);
                }

            } else {
                //peek next argument
                int nxt = i + 1;
                if(argv[nxt] != nullptr && CmdLineOptChecker::isValue(argv[nxt])) {
                    ptr_value = (argv[nxt]);
                    i = nxt;
                }
            }
        }
        //ptr_value should never be nullptr here (= error)
        bool optionSuccess = Option(varName, ptr_value);
        if(!optionSuccess) {
            return false;
        }
    }

    //no error -> SUCCESS
    return true;
}

bool CmdLineOptParser::Option(const char c, const char* info) {
    //For Debugging: just print the content
    if(info == nullptr) {
        // no value
        printf("Variable: %c = TRUE \n");
    } else {
        printf("Variable: %c = %s \n", c, info);
    }
    return true;
}