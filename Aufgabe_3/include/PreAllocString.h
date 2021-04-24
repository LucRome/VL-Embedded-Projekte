#define CREATE(varName , size) char varName##_buf[size + 1] = {0};\
PreAllocString varName(size, varName##_buf);

#include <cstddef>


class PreAllocString {
private:
    const char* buffer_start;
    const char* buffer_end;
    char* buffer_cur; // always points towards current '\\0'

    // const size_t size;

    bool writeChar(const char& chr);
    
public:
    const size_t size;

    // constructor
    PreAllocString(const size_t& size, char* buffer);

    // Convert Functions
    operator const char *() const;
    operator const void *() const; //TODO: test
    // Access Operator
    const char & operator [] (const int idx); //TODO: test

    /* Current number of characters in string */
    size_t GetLength() const;

    /* Maximum number of characters possible */
    //TODO
    // constexpr size_t SizeOf();

    /* Empty the string , set length field to zero */
    void Empty();

    PreAllocString& operator =( char rhs);
    PreAllocString& operator =(const char * rhs);
    PreAllocString& operator =( char * const rhs);

    PreAllocString& operator +=(char rhs);
    PreAllocString& operator +=(char const * rhs);

    void AddFormat ( const char* format , ... );
    void AddWhiteSpace ();
};