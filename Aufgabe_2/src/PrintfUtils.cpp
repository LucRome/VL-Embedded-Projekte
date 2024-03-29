#include "PrintfUtils.h"

namespace PrintfUtils {

    bool isSpecifier(const char* fmt) {
        if(fmt == nullptr) {
            return false;
        } else {
            SpecifierType st = getSpecifierType(fmt);
            return st != SpecifierType::None;
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
