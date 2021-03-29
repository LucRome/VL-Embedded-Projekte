#include "LiteralChecker.h"

bool LiteralChecker::isVariable(const char *arg)
{
    if (arg != nullptr)
    {
        //check first char
        if (*arg == '-')
        {
            //increment pointer by one (for second char)
            arg++;
            //check second char
            return isLetter(arg);
        }
    }
    //arg == nullptr || firstchar is wrong
    return false;
}

bool LiteralChecker::isValue(const char *arg)
{
    bool result = true;
    if (arg != nullptr)
    {
        while (result && (*arg != '\0'))
        {
            result = isLetter(arg) || isNumber(arg);
            arg++;
        }
    }

    return result;
}

bool LiteralChecker::isEquals(const char *arg)
{
    return (arg != nullptr) && ((*arg == '=') || (*arg == ' '));
}

bool LiteralChecker::EOA(const char *arg)
{
    return (arg != nullptr) && (*arg == '\0');
}

bool LiteralChecker::isLetter(const char *arg)
{
    return (arg != nullptr) && (((*arg >= 'A') && (*arg <= 'Z')) || (*arg >= 'a' && *arg <= 'z'));
}

bool LiteralChecker::isNumber(const char *arg)
{
    return (arg != nullptr) && (*arg >= '0' && *arg <= '9');
}