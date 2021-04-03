#include "catch.hpp"

#include <cstring>

#include "Printf.h"
#include "PrintfUtils.h"
#include "DestAppender.h"

////////////////////////////////////////////////////////
//  Utils
////////////////////////////////////////////////////////

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

TEST_CASE("Printf", "[Printf]") {
    char dst[20];
    void* end = dst + (sizeof(dst) / sizeof(dst[0]));

    SECTION("char") {
        char fmt[] = "Hello %c";
        char arg = 'A';
        char result[] = "Hello A";
        
        Printf(dst, end, fmt, arg);

        REQUIRE(strcmp(dst, result) == 0);
    }

    SECTION("signed int") {
        {
            char fmt[] = "Hello %d";
            signed int arg = -12334;
            char result[] = "Hello -12334";
            
            Printf(dst, end, fmt, arg);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
}