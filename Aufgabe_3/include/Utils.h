#pragma once
#include <stdarg.h>

namespace Utils {
    // char* writeFormat(char* dst, const void* end, const char* fmt, va_list params);


    /**
     * @brief specifiers: %d, %u, %c, %s, %x, %b
     * 
     * @param fmt format string
     * @return true specifier
     * @return false no specifier
     */
    bool isSpecifier(const char* fmt);

    /**
     * @brief End of String?
     * @param ptr_char ptr to char
     * @return true ptr_char == '\0'
     */
    bool EOS(const char* ptr_char);

    enum class SpecifierType {
        SignedInt, UnsignedInt, Char, String, Hexa, Binary, SkipFormat ,None
    };

    /**
     * @brief Get the type of Specifier
     * 
     * @param fmt ptr to specifier
     * @return SpecifierType the type of specifier (uint, char, ...)
     */
    SpecifierType getSpecifierType(const char* fmt);

    bool writeChar(char* dst, const void* end, char arg);

    char* processSpecifier(va_list& params, const SpecifierType specType, char* dst, const void* end);

    /////////////// Functions /////////////////
    char* process_c(const int* arg, char* dst, const void* end);
    char* process_d(signed int arg, char* dst, const void* end);
    char* process_u(unsigned int arg, char* dst, const void* end);
    char* process_s(char* arg, char* dst, const void* end);
    char* process_b(signed int arg, char* dst, const void* end);
    char* process_x(signed int arg, char* dst, const void* end);

}