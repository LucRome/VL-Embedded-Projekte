//Checks whether the given chars* matches a given type
//TODO

class LiteralChecker
{
public:
    //Variable: '-'[Letter]
    static bool isVariable(const char *arg);
    //Value: (Letter|Number)* '\0' (always to the end of the arg, otherwise error)
    static bool isValue(const char *arg);
    //Equals: '=' | ' '
    static bool isEquals(const char *arg);
    //EOA: '\0' (End of Argument)
    static bool EOA(const char *arg);

    // # of chars it takes to declare a Variable
    const int varLength = 2;

private:
    //Letter: [A-Za-z]
    static bool isLetter(const char *arg);
    //Number: [0-9]
    static bool isNumber(const char *arg);
};