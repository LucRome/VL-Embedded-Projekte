#include "PreAllocString.h"

bool PreAllocString::writeChar(const char& chr) {
    printf("write char: %c at pos: %i\n", chr, GetLength());
    if(GetLength() + 1 > SizeOf()) {
        return false;
    }
    std::cout<< "length: " << GetLength() << std::endl; 
    // Else
    *buffer_cur = chr;
    ++buffer_cur;
    *buffer_cur='\0';

    return true;
}

PreAllocString::PreAllocString(const size_t _size, char* _buffer_start)
    :buffer_start(_buffer_start) ,buffer_cur(_buffer_start), size(_size)
{
    if(!buffer_start) {
        return;
    }
    *buffer_cur = '\0';
}

// Access Operator
const char & PreAllocString::operator [] (const int idx) {
    size_t idx_d = idx;
    std::cout << "operator[idx], idx=" << idx_d << std::endl;
    if(idx_d > this->SizeOf()- 1) {
        // Error -> return '\0'
        return *buffer_cur;
    }
    // else
    return *(buffer_start + idx_d);
}

/* Current number of characters in string */
size_t PreAllocString::GetLength() const {
    return (buffer_cur - buffer_start);
}

/* Empty the string , set length field to zero */
void PreAllocString::Empty() {
    // Empty string
    buffer_cur = const_cast<char*>(buffer_start);
    // also reset start
    *buffer_cur = '\0';
}

PreAllocString& PreAllocString::operator =( char rhs) {
    this->Empty();
    if(!writeChar(rhs)) {
        //Error
        this->Empty();
    }
    return *this;
}

PreAllocString& PreAllocString::operator =(const char * rhs) {
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

PreAllocString& PreAllocString::operator =( char * const rhs) {
    this->Empty();
    if(rhs)
    {   
        const char* rhs_mut = const_cast<const char*>(rhs);
        this->operator=(rhs_mut);
    }
    return *this;
}

PreAllocString& PreAllocString::operator +=(char rhs) {
    if(!writeChar(rhs)) {
        printf("\n\n operator += char: write error");
        //Error
        this->Empty();
    }
    // else
    return *this;
}

PreAllocString& PreAllocString::operator +=(char const * rhs) {
    if(!rhs) {
        //error
        printf("Empty Pointer!! \n");
        this->Empty();
        return *this;
    }
    // Else
    const char* rhs_mov = rhs;
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

void PreAllocString::AddFormat ( const char* format , ... ) {
    if(format) {
        printf("\nadd Format: %s\n current buffer: %i", format, buffer_cur);
        //access "..."
        va_list params;
        va_start(params, format);

        bool success = true;
        while(!Utils::EOS(*format) && success) {
            if(Utils::isSpecifier(format)) {
                success = Utils::processSpecifier(params, Utils::getSpecifierType(format), *this);
                format += 2;
            } 
            else {
                success = this->writeChar(*format);
                format++;
            }
        }
        va_end(params);

        if(!success) {
            //Error
            this->Empty();
        }
    }
}

void PreAllocString::AddWhiteSpace () {
    // no possibility to communicate Error -> no need to catch
    writeChar(' ');
}