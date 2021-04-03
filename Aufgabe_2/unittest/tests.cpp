#include "catch.hpp"

#include <cstring>

#include "PrintfUtils.h"
#include "DestAppender.h"

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
        {
            char str[] = "%%"; //%a no specifier (but valid)
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

TEST_CASE("Utils::getSpecifierType", "[Utils]") {
    SECTION("Specifiers") {
        {
            char str[] = "%d";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::SignedInt);
        }
        {
            char str[] = "%u";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::UnsignedInt);
        }
        {
            char str[] = "%c";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::Char);
        }
        {
            char str[] = "%s";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::String);
        }
        {
            char str[] = "%x";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::Hexa);
        }
        {
            char str[] = "%b";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::Binary);
        }
    }
    SECTION("Others:") {
        {
            char str[] = "%%";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::SkipFormat);
        }
        {
            char str[] = "%k";
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::None);
        }
        {
            char* str = nullptr;
            REQUIRE_NOTHROW(PrintfUtils::getSpecifierType(str) 
                == PrintfUtils::SpecifierType::None);
        }
    }
}


////////////////////////////////////////////////////////
//  DestAppender
////////////////////////////////////////////////////////
TEST_CASE("DestAppender::appendChar", "[DestAppender]") {
    //Allocate dst
    const int dst_length = 6;
    char dst[dst_length] = "abcde";

    DestAppender dstAppender = DestAppender(dst, dst + dst_length - 1);

    REQUIRE(!dstAppender.blocked);

    SECTION("Correct:") {      
        {
            char result[dst_length] = "12345";
            for(int i = 0; i < dst_length - 1; i++) {
                REQUIRE(dstAppender.appendCharToDest(result[i]));
            }
            //No place for '\0' anymore
            REQUIRE_FALSE(dstAppender.appendCharToDest('6'));
            REQUIRE(strcmp(result, dstAppender.getDst_start()) == 0);
        }
    }
}