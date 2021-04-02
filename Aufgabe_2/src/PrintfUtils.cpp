#include "PrintfUtils.h"

namespace PrintfUtils {

    int getNeededNrOfArguments(const char* fmt) {
        if(!fmt) {
            return -1;
        } else {
            int nrArgs = 0;
            //iterate over fmt until terminated
            while(!EOS(fmt)) {
                //check if % and next is a specifier 
                if(isSpecifier(fmt)) {
                    nrArgs++;
                }
                fmt++;
            }

            return nrArgs;
        }
    };

    bool isSpecifier(const char* fmt) {
        if(fmt == nullptr) {
            return false;
        } else {
            SpecifierType st = getSpecifierType(fmt);
            return st == SpecifierType::None || st == SpecifierType::SkipFormat;
        }
    }

    bool EOS(const char* ptr_char) {
        return (ptr_char != nullptr) && (*ptr_char == '\0');
    }

    SpecifierType getSpecifierType(const char* fmt) {
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
}
