//Checks whether the given chars* matches a given type
//TODO

class CmdLineOptChecker
{
public:
    //Variable: '-'[Letter]
    static bool isVariable(const char* arg);
    //Value: (Letter|Number)* '\0' (always to the end of the arg, otherwise error)
    static bool isValue(const char* arg);
    //Equals: '='
    static bool isEquals(const char* arg);
    //EOA: '\0' (End of Argument)
    static bool EOA(const char* arg);

private:
    static bool isLetter(const char* arg);
    static bool isNumber(const char* arg);
};