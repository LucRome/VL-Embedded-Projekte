class DestAppender {
public:
    DestAppender(char* dst, const void* end);

    //returns: False when char can't be appended
    bool appendCharToDest(const char& charToAppend);
    bool blocked;
    void resetDst();
    const char* getDst_start() const;
private:
    const char* dst_start;
    char* dst_current; //always points to '\0'
    const void* end;
};