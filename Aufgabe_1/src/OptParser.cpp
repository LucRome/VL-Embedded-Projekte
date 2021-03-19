class CmdLineOptParser
{
public:
    virtual ~CmdLineOptParser () = default;

    // returns true , if all arguments are successfully parsed.
    bool Parse(int argc , char* argv []);

protected:
    // returns true , if option was successfully parsed.
    virtual bool Option(const char c, const char* info);
};