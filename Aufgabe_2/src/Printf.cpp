#include "Printf.h"
#include "PrintfUtils.h"

#include <stdarg.h>

char* Printf(char* dst, const void* end, const char* fmt, ...) {
    
    if(!dst || !end || !fmt) {
        return nullptr;
    }
    else {
        int argc_expected = PrintfUtils::getNeededNrOfArguments(fmt);
    
        if(argc_expected != -1) { // valid
            //access "..."
            // va_list params;
            // va_start(params, argc_expected);

            while(!PrintfUtils::EOS(fmt)) {
                if(PrintfUtils::isSpecifier(fmt)) {
                    //TODO process specifiers
                } 
                else {
                    //TODO process chars

                }
            }
        }
    }

    return nullptr;
}