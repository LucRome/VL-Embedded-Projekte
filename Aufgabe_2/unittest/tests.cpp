#include "catch.hpp"
#include "PrintfUtils.h"

////////////////////////////////////////////////////////
//  Utils
////////////////////////////////////////////////////////
TEST_CASE("Utils::isSpecifier", "[Utils]") {
    SECTION("Correct") {
        {
            char str[] = "%d, %u, %c, %s, %x, %b, %%"; //all specifiers (%% = escape format)
            REQUIRE_NOTHROW(PrintfUtils::getNeededNrOfArguments(str) == 6);
        }
        {
            char str[] = "%s, %"; //% as last char isn't catched here
            REQUIRE_NOTHROW(PrintfUtils::getNeededNrOfArguments(str) == 1);
        }
        {
            char str[] = "%a Hello World"; //%a no specifier (but valid)
            REQUIRE_NOTHROW(PrintfUtils::getNeededNrOfArguments(str) == 0);
        }
    }
    SECTION("Error") {
        {
            char* str = nullptr;
            REQUIRE_NOTHROW(PrintfUtils::getNeededNrOfArguments(str) == -1);
        }
    } 
}