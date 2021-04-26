#pragma once

#define CREATE(varName , size) char varName##_buf[size + 1] = {0};\
PreAllocString varName(size, varName##_buf);


#include "Utils.h"

#include <stdarg.h>
#include <cstddef>
#include <iostream>

// TODO: maybe use abstract class to prevent code Bloat with Template 

class PreAllocString {
private:
    const char* buffer_start;
    const char* buffer_end;
    char* buffer_cur; // always points towards current '\\0'
    const size_t size; //Const ->Problem
    
public:
    bool writeChar(const char& chr);

    // constructor
    PreAllocString(const size_t size, char* buffer_start);
    // Convert Functions
    operator const char *() const { return buffer_start; }
    operator const void *() const { return buffer_start; }

    // Access Operator
    const char & operator [] (const int idx);

    /* Current number of characters in string */
    size_t GetLength() const;
    /* Maximum number of characters possible */
    //TODO
    constexpr size_t SizeOf() { return size; }

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