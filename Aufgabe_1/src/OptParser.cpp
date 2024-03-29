#include "OptParser.h"
#include "LiteralChecker.h"
#include <stdio.h>

bool CmdLineOptParser::Parse(int argc, char *argv[])
{

    //iterate over all arguments and check them
    //only while result is not false
    for (int i = 1; i < argc; i++)
    {
        char varName = 0;
        char *ptr_value = nullptr;

        //must start with Variable
        if (argv[i] == nullptr || !LiteralChecker::isVariable(argv[i]))
        {
            return false;
        }
        else
        {
            //+ 1: '-'x (argv[i] points to '-' and x is needed)
            int offset = 1;
            varName = *(argv[i] + offset);

            // get value
            offset = 2;
            if (!LiteralChecker::EOA(argv[i] + offset))
            {
                //-> Value or Equals

                if (LiteralChecker::isEquals(argv[i] + offset))
                {
                    offset++; //ignore Equals
                }

                if (!LiteralChecker::isValue(argv[i] + offset))
                {
                    return false;
                }
                else
                {
                    ptr_value = (argv[i] + offset);
                }
            }
            else
            {
                //peek next argument
                int nxt = i + 1;
                if (nxt < argc && argv[nxt] != nullptr && LiteralChecker::isValue(argv[nxt]))
                {
                    ptr_value = (argv[nxt]);
                    i = nxt;
                }
            }
        }
        //ptr_value should never be nullptr here (= error)
        bool optionSuccess = Option(varName, ptr_value);
        if (!optionSuccess)
        {
            return false;
        }
    }

    //no error -> SUCCESS
    return true;
}

bool CmdLineOptParser::Option(const char, const char *)
{
    return true;
}