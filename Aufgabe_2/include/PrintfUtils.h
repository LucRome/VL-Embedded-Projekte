namespace PrintfUtils {    
    /**
     * @brief Get the Needed Nr Of Arguments
     * 
     * @param fmt format string
     * @return int nr of expected arguments (-1 = error)
     */
    int getNeededNrOfArguments(const char* fmt);

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
}