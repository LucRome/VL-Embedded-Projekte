#include "Utils.h"
#include <climits>
#include <stdio.h>

#include "PreAllocString.h"

bool Utils::isSpecifier(const char* fmt) {
    if(fmt == nullptr) {
        return false;
    } else {
        SpecifierType st = getSpecifierType(fmt);
        return st != SpecifierType::None;
    }
}

bool Utils::EOS(const char& ptr_char) {
    return ptr_char == '\0';
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


////////////////////////////////
// Processfkt. for the Specifiers
////////////////////////////////

bool Utils::process_c(const int* arg, PreAllocString& pas) {
    if(!arg) {
        return false;
    }
    // else //
    return pas.writeChar(*arg);
}

bool Utils::process_d(signed int arg, PreAllocString& pas) {    
    bool success = true;
    unsigned int abs;
    if(arg < 0) {
        success = pas.writeChar('-');
        abs = arg * (-1);
    } else {
        abs = arg;
    }
    if(success) {
        return process_u(abs, pas);
    } else {
        return !success;
    }
}

bool Utils::process_u(unsigned int arg, PreAllocString& pas) {
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
        success = pas.writeChar(buffer[i] + '0');
        i--;
    }

    return success;
}

bool Utils::process_s(char* arg, PreAllocString& pas) {
    if(!arg) {
        return false;
    }
    // else //
    bool success;
    do {
        printf("\nprocess_s: write Char: %c", *arg);
        success = pas.writeChar(*arg);
        arg++;
    } while(success && !EOS(*arg));

    return success;
}

const int int_length = 32; 

bool Utils::process_b(signed int arg, PreAllocString& pas) {
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
    success = pas.writeChar('0') && pas.writeChar('b');

    // write 0/1 to dst
    while (success && (mask > 0)) {
        if((uInt & mask) > 0) { //Bit set -> write 1
            success = pas.writeChar('1');
        } else { //write 0
            success = pas.writeChar('0');
        }
        mask = mask >> 1; // =: x/2
    }
    
    return success;
}

const char hexSymbols[] = { '0','1','2','3',
                            '4','5','6','7',
                            '8','9','a','b',
                            'c','d','e','f'
                        };

const int hexWidth = 4;

bool Utils::process_x(signed int arg, PreAllocString& pas) {
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
    success = pas.writeChar('0') && pas.writeChar('x');

    // write hexSymbol to dst
    while (success && (mask > 0)) {
        rshifts -= hexWidth;
        int nr = (uInt & mask) >> rshifts;
        success = pas.writeChar(hexSymbols[nr]);
        mask = mask >> hexWidth;
    }
    
    return success;
}



bool Utils::processSpecifier(va_list& params, const SpecifierType specType, PreAllocString& pas) {  
    bool ret;
    switch (specType)
        {
        case SpecifierType::Binary: {
            signed int i = va_arg(params, signed int);
            ret = process_b(i, pas);
            break;
        }
        case SpecifierType::Char: {
            int i = va_arg(params, int);
            ret = process_c(&i, pas);
            break;
        }
        case SpecifierType::Hexa: {
            signed int i = va_arg(params, signed int);
            ret = process_x(i, pas);
            break;
        }
        case SpecifierType::SignedInt: {
            signed int i = va_arg(params, signed int);
            ret = process_d(i, pas);
            break;
        }
        case SpecifierType::String: {
            char* arg = va_arg(params, char*);
            ret = process_s(arg, pas);
            break;
        }
        case SpecifierType::UnsignedInt: {
            unsigned int i = va_arg(params, unsigned int);
            ret = process_u(i, pas);
            break;
        }
        case SpecifierType::SkipFormat:
            ret = pas.writeChar('%');
            break;
        default:
            ret = false;
            break;
        }
    return ret;
}