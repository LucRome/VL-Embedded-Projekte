#include "OptChecker.h"

bool CmdLineOptChecker::isVariable(const char* arg) {
    if(arg != nullptr) {
        //check first char
        if(*arg == '-') {
            //increment pointer by one (for second char)
            arg++;
            //check second char
            return isLetter(arg);
        }
    }
    //arg == nullptr || firstchar is wrong
    return false;
}

bool CmdLineOptChecker::isValue(const char* arg) {
    bool result = true;
    if(arg != nullptr) {
        while (result && (*arg != '\0')) {
            result = isLetter(arg) || isNumber(arg);
            arg++;
        }
    }
}

bool CmdLineOptChecker::isEquals(const char* arg) {
    return (arg != nullptr) && (*arg == '=');
}

bool CmdLineOptChecker::EOA(const char* arg) {
    return (arg != nullptr) && (*arg == '\0');
}

bool CmdLineOptChecker::isLetter(const char* arg) {
    return (arg != nullptr) && (*arg >= 'A' && *arg <= 'Z') || (*arg >= 'a' && *arg <= 'z');
}

bool CmdLineOptChecker::isNumber(const char* arg) {
    return (arg != nullptr) && (*arg >= '0' && *arg <= '9');
}