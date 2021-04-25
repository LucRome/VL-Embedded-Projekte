#include "Utils.h"
#include <climits>
#include <stdio.h>


bool Utils::isSpecifier(const char* fmt) {
    if(fmt == nullptr) {
        return false;
    } else {
        SpecifierType st = getSpecifierType(fmt);
        return st != SpecifierType::None;
    }
}

bool Utils::EOS(const char* ptr_char) {
    return (ptr_char != nullptr) && (*ptr_char == '\0');
}

Utils::SpecifierType Utils::getSpecifierType(const char* fmt) {
    if(!fmt || *fmt != '%') {
        return SpecifierType::None;
    } 
    else {
        fmt++;
        switch (*fmt)
        {
        case 'd':
            return SpecifierType::SignedInt;
        case 'u':
            return SpecifierType::UnsignedInt;
        case 'c':
            return SpecifierType::Char;
        case 's':
            return SpecifierType::String;
        case 'x':
            return SpecifierType::Hexa;
        case 'b':
            return SpecifierType::Binary;
        case '%':
            return SpecifierType::SkipFormat;
        default:
            return SpecifierType::None;
        }
    }
}

bool Utils::writeChar(char* dst, const void* end, char arg) {
    if(!dst || !end || dst + 1 == end) {
        return false;
    }
    //Else
    *dst = arg;
    return true;
}


////////////////////////////////
// Processfkt. for the Specifiers
////////////////////////////////

char* Utils::process_c(const int* arg, char* dst, const void* end) {
    if(!arg || !dst || !end) {
        return nullptr;
    }
    // else //
    if (writeChar(dst, end, *arg)) {
        return dst + 1;
    } else {
        return nullptr;
    }
}

char* Utils::process_d(signed int arg, char* dst, const void* end) {
    if(!dst|| !end) {
        return nullptr;
    }
    
    bool success = true;
    unsigned int abs;
    if(arg < 0) {
        success = writeChar(dst, end, '-');
        dst++;
        abs = arg * (-1);
    } else {
        abs = arg;
    }
    if(success) {
        return process_u(abs, dst, end);
    } else {
        return nullptr;
    }
}

char* Utils::process_u(unsigned int arg, char* dst, const void* end) {
    if(!dst|| !end) {
        return nullptr;
    }

    bool success = true;
    const int buffer_length = 11;
    char buffer[buffer_length] = { 0 };
    int i = 0;

    //put arg in char-buffer
    while(success && arg > 0) {
        int nr = arg % 10;
        buffer[i] = nr;
        arg /= 10; 
        i++;       
    }

    //skip front 0
    i = buffer_length - 1;
    while(buffer[i] == 0) {
        i--;
    }

    //write rest to dest
    while(success && i >= 0) {
        success = writeChar(dst, end, buffer[i] + '0');
        dst++;
        i--;
    }

    if(!success) {
        return nullptr;
    }
    return dst;
}

char* Utils::process_s(char* arg, char* dst, const void* end) {
    printf("Utils::process_s: dst=%i",dst);
    if(!dst|| !end || !arg) {
        return nullptr;
    }
    // else //
    bool success;
    do {
        printf("\nprocess_s: write Char: %c", *arg);
        success = writeChar(dst, end, *arg);
        dst++;
        arg++;
    } while(success && !EOS(arg));
    
    if(!success) {
        printf("\nError in WriteChar, Utils\n");
        return nullptr;
    }
    printf("Utils::process_s return: dst=%i",dst);

    return dst;
}

const int int_length = 32; 

char* Utils::process_b(signed int arg, char* dst, const void* end) {
    if(!dst|| !end) {
        return nullptr;
    }

    unsigned int uInt;
    //Handling of negative numbers
    if(arg < 0) {
        uInt = UINT_MAX + 1 + arg; // (= UINT_MAX + 1 - |arg|)
    } else {
        uInt = arg;
    }

    // write bits to out with the help of logical operators
    unsigned int mask = 1 << (int_length - 1); //highest Bit of int

    //skip 0 at front:
    while (mask > 0 && (uInt & mask) == 0) {
        mask = mask >> 1;
    }

    bool success = true;
    //write prefix (0b)
    success = writeChar(dst, end, '0');
    dst++;
    success = success && writeChar(dst, end, 'b');
    dst++;

    // write 0/1 to dst
    while (success && (mask > 0)) {
        if((uInt & mask) > 0) { //Bit set -> write 1
            success = writeChar(dst, end, '1');
            dst++;
        } else { //write 0
            success = writeChar(dst, end, '0');
            dst++;
        }
        mask = mask >> 1; // =: x/2
    }
    
    if(!success) {
        return nullptr;
    }
    return dst;
}

const char hexSymbols[] = { '0','1','2','3',
                            '4','5','6','7',
                            '8','9','a','b',
                            'c','d','e','f'
                        };

const int hexWidth = 4;

char* Utils::process_x(signed int arg, char* dst, const void* end) {
    if(!dst|| !end) {
        return nullptr;
    }

    unsigned int uInt;
    //handle negative nr.
    if(arg < 0) {
        uInt = UINT_MAX + 1 + arg; // (= UINT_MAX + 1 - |arg|)
    } else {
        uInt = arg;
    }

    // write bits to out with the help of logical operators
    unsigned int mask = 0xF << (int_length - hexWidth); //highest 4Bits of int

    int rshifts = int_length;
    //skip 0 at front:
    while (mask > 0 && (uInt & mask) == 0) {
        mask = mask >> hexWidth;
        rshifts -= hexWidth;
    }

    bool success = true;

    // write prefix (0x)
    success = writeChar(dst, end, '0');
    dst++;
    success = success && writeChar(dst, end, 'x');
    dst++;

    // write hexSymbol to dst
    while (success && (mask > 0)) {
        rshifts -= hexWidth;
        int nr = (uInt & mask) >> rshifts;
        success = writeChar(dst, end, hexSymbols[nr]);
        dst++;
        mask = mask >> hexWidth;
    }
    
    if(!success) {
        return nullptr;
    }
    return dst;

}



char* Utils::processSpecifier(va_list& params, const SpecifierType specType, char* dst, const void* end) {
    if(!dst|| !end) {
        return nullptr;
    }
    
    char* ret;
    switch (specType)
        {
        case SpecifierType::Binary: {
            signed int i = va_arg(params, signed int);
            ret = process_b(i, dst, end);
            break;
        }
        case SpecifierType::Char: {
            int i = va_arg(params, int);
            ret = process_c(&i, dst, end);
            break;
        }
        case SpecifierType::Hexa: {
            signed int i = va_arg(params, signed int);
            ret = process_x(i, dst, end);
            break;
        }
        case SpecifierType::SignedInt: {
            signed int i = va_arg(params, signed int);
            ret = process_d(i, dst, end);
            break;
        }
        case SpecifierType::String: {
            char* arg = va_arg(params, char*);
            ret = process_s(arg, dst, end);
            break;
        }
        case SpecifierType::UnsignedInt: {
            unsigned int i = va_arg(params, unsigned int);
            ret = process_u(i, dst, end);
            break;
        }
        case SpecifierType::SkipFormat:
            if(writeChar(dst, end, '%')) {
                ret = dst++;
            } else {
                ret = nullptr;
            }
            break;
        default:
            ret = nullptr;
            break;
        }
    return ret;
}