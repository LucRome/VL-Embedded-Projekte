#include "Printf.h"
#include "PrintfUtils.h"
#include "DestAppender.h"

#include <stdarg.h>

namespace
{
    using namespace ::PrintfUtils;

    bool processSpecifier(va_list &params, const PrintfUtils::SpecifierType specType, DestAppender &dstApp)
    {
        bool success = true;
        switch (specType)
        {
        case SpecifierType::Binary:
        {
            signed int i = va_arg(params, signed int);
            success = dstApp.process_b(i);
            break;
        }
        case SpecifierType::Char:
        {
            int i = va_arg(params, int);
            success = dstApp.process_c(&i);
            break;
        }
        case SpecifierType::Hexa:
        {
            signed int i = va_arg(params, signed int);
            success = dstApp.process_x(i);
            break;
        }
        case SpecifierType::SignedInt:
        {
            signed int i = va_arg(params, signed int);
            success = dstApp.process_d(i);
            break;
        }
        case SpecifierType::String:
        {
            char *arg = va_arg(params, char *);
            success = dstApp.process_s(arg);
            break;
        }
        case SpecifierType::UnsignedInt:
        {
            unsigned int i = va_arg(params, unsigned int);
            success = dstApp.process_u(i);
            break;
        }
        case SpecifierType::SkipFormat:
            success = dstApp.appendCharToDest('%');
            break;
        default:
            success = false;
            break;
        }
        return success;
    }
}

using namespace PrintfUtils;

char *Printf(char *dst, const void *end, const char *fmt, ...)
{

    DestAppender destAppender = DestAppender(dst, end);

    if (!dst || !end || !fmt)
    {
        return nullptr;
    }
    else
    {
        const char *safePos = fmt;
        bool success = true;
        //access "..."
        va_list params;
        va_start(params, fmt);

        while (!PrintfUtils::EOS(fmt) && success)
        {
            safePos = fmt;
            if (PrintfUtils::isSpecifier(fmt))
            {
                success = processSpecifier(params, PrintfUtils::getSpecifierType(fmt), destAppender);
                fmt += 2;
            }
            else
            {
                success = destAppender.appendCharToDest(*fmt);
                fmt++;
            }
        }
        va_end(params);

        if (!success)
        {
            //Error
            return const_cast<char *>(safePos);
        }
    }
    return const_cast<char *>(fmt); //fmt at end (*fmt == '\0')
}