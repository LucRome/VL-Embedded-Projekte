namespace PrintfUtils {
    /* returns the nr. of Arguments that is needed to fill the fmt string
       -1 =: error
    */
    int getNeededNrOfArguments(const char* fmt);

    // true if char is a specifier (when after %)
    //specifiers: %d, %u, %c, %s, %x, %b
    bool isSpecifier(const char* fmt);
    //End of string = '\0'
    bool EOS(const char* ptr_char);
}