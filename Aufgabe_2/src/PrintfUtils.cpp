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
        bool result = (fmt != nullptr) && (*fmt == '%');
        fmt++;
        result = result && ((*fmt == 'd') || (*fmt == 'u') || (*fmt == 'c') ||
            (*fmt == 's') || (*fmt == 'x') || (*fmt == 'b'));
        return result;
    }

    bool EOS(const char* ptr_char) {
        return (ptr_char != nullptr) && (*ptr_char == '\0');
    }
}
