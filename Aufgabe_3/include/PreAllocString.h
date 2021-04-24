#define CREATE(varName , size)\
PreAllocString<size> varName;

#include <cstddef>
#include <iostream>

// TODO: maybe use abstract class to prevent code Bloat with Template 

template<int N>
class PreAllocString {
private:
    const char buffer_start[N+1] = {0};
    const char* buffer_end;
    char* buffer_cur; // always points towards current '\\0'
    const size_t size;

    // const size_t size;

    bool writeChar(const char& chr) {
        printf("write char: %c \n", chr);
        if(buffer_cur == buffer_end || GetLength() + 1 > size) {
            return false;
        } 
        // Else
        *buffer_cur = chr;
        ++buffer_cur;
        *buffer_cur='\0';

        return true;
    }
    
public:

    // constructor
    constexpr PreAllocString()
        :buffer_end(buffer_start + N + 1) ,buffer_cur(const_cast<char*>(buffer_start)), size(N)
    {
        // else
        *buffer_cur = '\0';
    }

    // Convert Functions
    operator const char *() const {
        return buffer_start;
    }
    operator const void *() const {
        return buffer_start;
    }
    // Access Operator
    const char & operator [] (const int idx) {
        size_t idx_d = idx;
        std::cout << "operator[idx], idx=" << idx_d << std::endl;
        if(idx_d > this->size - 1) {
            // Error -> return '\0'
            return *buffer_cur;
        }
        // else
        return *(buffer_start + idx_d);
    }

    /* Current number of characters in string */
    size_t GetLength() const {
        return (buffer_cur - buffer_start);
    }

    /* Maximum number of characters possible */
    //TODO
    constexpr size_t SizeOf() {
        return N;
    }

    /* Empty the string , set length field to zero */
    void Empty() {
        // Empty string
        while(buffer_cur > buffer_start) {
            *buffer_cur = '\0';
            buffer_cur--;
            printf("buffer empty: size = %i", GetLength());
        }
        // also reset start
        *buffer_cur = '\0';
    }

    PreAllocString& operator =( char rhs) {
        this->Empty();
        if(!writeChar(rhs)) {
            //Error
            this->Empty();
        }
        return *this;
    }

    PreAllocString& operator =(const char * rhs) {
        this->Empty();
        if(rhs)
        {
            while(*rhs != '\0') {
                if(!writeChar(*rhs)) {
                    // Error
                    this->Empty();
                    return *this;
                }
                rhs++;
            }
        }
        return *this;
    }

    PreAllocString& operator =( char * const rhs) {
        this->Empty();
        if(rhs)
        {   
            const char* rhs_mut = const_cast<const char*>(rhs);
            this->operator=(rhs_mut);
        }
        return *this;
    }

    PreAllocString& operator +=(char rhs) {
        if(!writeChar(rhs)) {
            //Error
            this->Empty();
        }
        // else
        return *this;
    }

    PreAllocString& operator +=(char const * rhs) {
        if(!rhs) {
            //error
            printf("Empty Pointer!! \n");
            this->Empty();
            return *this;
        }
        // Else
        const char* rhs_mov = const_cast<const char*>(rhs);
        while (*rhs_mov != '\0') {
            if(!writeChar(*rhs_mov)) {
                // Error
                this->Empty();
                return *this;
            }
            rhs_mov++;
        }
        return *this;
    }

    // void AddFormat ( const char* format , ... ); TODO
    void AddWhiteSpace () {
        // no possibility to communicate Error -> no need to catch
        writeChar(' ');
    }
};