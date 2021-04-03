#include "Printf.h"
#include "PrintfUtils.h"
#include "DestAppender.h"

#include <stdarg.h>

namespace {
    using namespace::PrintfUtils;

    bool processSpecifier(va_list& params, const PrintfUtils::SpecifierType specType, DestAppender& dstApp) {
        switch (specType)
            {
            case SpecifierType::Binary:
                break;
            case SpecifierType::Char: {
                int i = va_arg(params, int);
                dstApp.process_c(&i);
                break;
            }
            case SpecifierType::Hexa:
                break;
            case SpecifierType::None:
                break;
            case SpecifierType::SignedInt: {
                signed int i = va_arg(params, signed int);
                dstApp.process_d(i);
                break;
            }
            case SpecifierType::SkipFormat:
                break;
            case SpecifierType::String:
                break;
            case SpecifierType::UnsignedInt:
                break;
            default:
                break;
            }
        return true;
    }
}

using namespace PrintfUtils;

char* Printf(char* dst, const void* end, const char* fmt, ...) {
    
    DestAppender destAppender = DestAppender(dst, end);

    if(!dst || !end || !fmt) {
        return nullptr;
    }
    else {
        bool success = true;
        //access "..."
        va_list params;
        va_start(params, fmt);

        while(!PrintfUtils::EOS(fmt) && success) {
            if(PrintfUtils::isSpecifier(fmt)) {
                success = processSpecifier(params, PrintfUtils::getSpecifierType(fmt), destAppender);
                
                fmt += 2;
            } 
            else {
                success = destAppender.appendCharToDest(*fmt);
                fmt++;
            }
        }
    }
    if(!PrintfUtils::EOS(fmt)) {
        //Error
        return const_cast<char*>(fmt);
    }
    return nullptr;
}