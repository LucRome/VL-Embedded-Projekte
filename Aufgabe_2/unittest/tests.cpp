#include "catch.hpp"

#include <cstring>
#include <climits>

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
    char dst[80];
    void* end = dst - 1 + (sizeof(dst) / sizeof(dst[0]));

    SECTION("char") {
        char fmt[] = "Hello %c";
        char arg = 'A';
        char result[] = "Hello A";
        
        Printf(dst, end, fmt, arg);
        REQUIRE(strcmp(dst, result) == 0);
    }

    SECTION("signed int") {
        SECTION("standard") {
            char fmt[] = "Hello %d";
            signed int arg = -12334;
            char result[] = "Hello -12334";
            
            Printf(dst, end, fmt, arg);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("MAX") {
            char fmt[] = "Hello %d";
            signed int arg = INT_MAX;
            char result[] = "Hello 2147483647";
            
            Printf(dst, end, fmt, arg);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
    SECTION("unsigned int") {
        SECTION("standard") {
            char fmt[] = "Hello %u";
            unsigned int arg = 12334;
            char result[] = "Hello 12334";
            
            Printf(dst, end, fmt, arg);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("MAX") {
            char fmt[] = "Hello %u";
            signed int arg = UINT_MAX;
            char result[] = "Hello 4294967295";
            
            Printf(dst, end, fmt, arg);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
    SECTION("string") {
        SECTION("one") {
            char fmt[] = "Hello %s";
            char arg[] = "12334";
            char result[] = "Hello 12334";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("two") {
            char fmt[] = "Hello %s How are %s";
            char arg1[] = "Carl,";
            char arg2[] = "you.";
            char result[] = "Hello Carl, How are you.";
            
            Printf(dst, end, fmt, arg1, arg2);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
    SECTION("binary") {
        SECTION("one") {
            char fmt[] = "B: %b";
            signed int arg = 61276;
            char result[] = "B: 1110111101011100";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("two") {
            char fmt[] = "Neg: %b";
            signed int arg = INT_MIN; //-2.147.483.648
            char result[] = "Neg: 10000000000000000000000000000000";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("three") {
            char fmt[] = "Neg: %b";
            signed int arg = -1;
            char result[] = "Neg: 11111111111111111111111111111111";
                                    
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("four") {
            char fmt[] = "Pos: %b";
            signed int arg = INT_MAX; // 2147483647
            char result[] = "Pos: 1111111111111111111111111111111";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
    SECTION("hex") {
        SECTION("one") {
            char fmt[] = "X: %x";
            signed int arg = 61276;
            char result[] = "X: EF5C";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("two") {
            char fmt[] = "Neg: %x";
            signed int arg = INT_MIN; //-2.147.483.648
            char result[] = "Neg: 80000000";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("three") {
            char fmt[] = "Neg: %x";
            signed int arg = -1;
            char result[] = "Neg: FFFFFFFF";
                                    
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
        SECTION("four") {
            char fmt[] = "Pos: %x";
            signed int arg = INT_MAX; // 2147483647
            char result[] = "Pos: 7FFFFFFF";
            
            Printf(dst, end, fmt, arg);
            printf("%s == %s\n", dst, result);
            REQUIRE(strcmp(dst, result) == 0);
        }
    }
}

TEST_CASE("Printf: out of bounds", "[Printf]") {
    SECTION("standard 1") {
        char dst[5] = {0};
        char* end = dst + sizeof(dst) - 1;

        char fmt[] = "ABCDEFGHI";
        char* res = Printf(dst, end, fmt);
        printf("end: %c\n", *end);
        printf("dst: %s\n", dst);
        printf("%s == %s\n", res, fmt + 4);
        REQUIRE(strcmp(res, (fmt + 4)) == 0);
    }
    SECTION("standard") {
        char dst[9] = {0};
        char* end = dst + sizeof(dst) - 1;

        char fmt[] = "ABCDEFGH2";
        char* res = Printf(dst, end, fmt);
        printf("end: %c\n", *end);
        printf("fmt: %s\n", fmt);
        printf("%s == %s\n", res, fmt + 8);
        REQUIRE(strcmp(res, (fmt + 8)) == 0);
    }
}