#include "catch.hpp"

# include "PreAllocString.h"
#include <cstring>
#include <climits>

TEST_CASE("Assignments") {
    CREATE(pas1, 20);

    pas1 = "Hello";
    PreAllocString& pas2 = pas1;
    PreAllocString pas3 = pas1;

    pas2 += "45";

    REQUIRE(strcmp(pas1.operator const char *(), pas2.operator const char *()) == 0);
    REQUIRE(strcmp(pas1.operator const char *(), pas3.operator const char *()) == 0);
}

TEST_CASE("Correct") {
    SECTION("Macro + operator+=(char)") {
        CREATE(pas, 20);
        // REQUIRE(pas.SizeOf() == 20);
        REQUIRE(pas.GetLength() == 0);
        for(int i = 0; i < 19; i++) {
            pas += 'a';
        }
        REQUIRE(pas.GetLength() == 19);
        pas.Empty();
        REQUIRE(pas.GetLength() == 0);
    }
    SECTION("operator=") {
        {
            CREATE(pas, 7);
            char rhs = 'a';
            pas=rhs;
            REQUIRE(pas[0] == rhs);
            REQUIRE(pas[1] == '\0');
        }
        {
            CREATE(pas, 7);

            char rhs[] = "ABCDEF";
            const char* rhs_ptr = rhs;
            pas=rhs_ptr;
            REQUIRE(strcmp(pas.operator const char *(), rhs) == 0);
        }
        {

            CREATE(pas, 7);
            
            char rhs[] = "ABCDEF";
            char * const rhs_ptr = rhs;

            pas=rhs_ptr;
            REQUIRE(strcmp(pas.operator const char *(), rhs) == 0);
        }
    }

    SECTION("operator+=, addWhiteSpace") {
        CREATE(pas, 10);
        {
            char res[] = "aa";
            pas += 'a';
            pas += 'a';
            REQUIRE(strcmp(pas.operator const char *(), res) == 0);
        }
        {
            char res[] = "aa ";
            pas.AddWhiteSpace();
            REQUIRE(strcmp(pas.operator const char *(), res) == 0);
        }
        {

            char res[] = "aa ABCDE";
            char rhs[] = "ABCDE";
            char const * rhs_ptr = rhs;
            pas += rhs_ptr;
            REQUIRE(strcmp(pas.operator const char *(), res) == 0);
        }
    }
}

TEST_CASE("Error") {
    SECTION("operator=") {
        CREATE(pas, 5);
        {
            char rhs[] = "ABCDEFG";
            const char * rhs_ptr = rhs;
            pas = rhs_ptr;
            REQUIRE(pas.GetLength() == 0);
            REQUIRE(pas[0] == '\0');
        }
        {
            char rhs[] = "ABCDEF";
            char * const rhs_ptr = rhs;
            pas = rhs_ptr;
            int i = pas.SizeOf();
            REQUIRE(pas.GetLength() == 0);
            REQUIRE(pas[0] == '\0');
        }
    }
    SECTION("operator+=") {
        {
            CREATE(pas, 5);
            for(int i = 0; i < 6; i++) { //leaves no place for '\0'
                pas += 'a';
            }
            REQUIRE(pas.GetLength() == 0);
            REQUIRE(pas[0] == '\0');
        }
        {
            CREATE(pas, 8);
            char rhs[] = "ABCD";
            char rhs2[] = "ABCDE";
            char const * rhs_ptr = rhs;
            char const * rhs2_ptr = rhs2;
            pas += rhs_ptr;
            pas += rhs2_ptr;
            REQUIRE(pas.GetLength() == 0);
            REQUIRE(pas[0] == '\0');
        }
    }
}

TEST_CASE("AddFormat") {
    CREATE(pas, 80);

    SECTION("char") {
        char fmt[] = "Hello %c";
        char arg = 'A';
        char result[] = "Hello A";
        
        pas.AddFormat(fmt, arg);
        REQUIRE(strcmp(pas.operator const char *(), result) == 0);

        pas.Empty();
    }

    SECTION("signed int") {
        SECTION("standard") {
            char fmt[] = "Hello %d";
            signed int arg = -12334;
            char result[] = "Hello -12334";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);
            
            pas.Empty();
        }
        SECTION("MAX") {
            char fmt[] = "Hello %d";
            signed int arg = INT_MAX;
            char result[] = "Hello 2147483647";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
    }
    SECTION("unsigned int") {
        SECTION("standard") {
            char fmt[] = "Hello %u";
            unsigned int arg = 12334;
            char result[] = "Hello 12334";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("MAX") {
            char fmt[] = "Hello %u";
            signed int arg = UINT_MAX;
            char result[] = "Hello 4294967295";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
    }
    SECTION("string") {
        SECTION("one") {
            char fmt[] = "Hello %s";
            char arg[] = "12334";
            char result[] = "Hello 12334";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("two") {
            char fmt[] = "Hello %s How are %s";
            char arg1[] = "Carl,";
            char arg2[] = "you.";
            char result[] = "Hello Carl, How are you.";
            
            pas.AddFormat(fmt, arg1, arg2);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
    }
    SECTION("binary") {
        SECTION("one") {
            char fmt[] = "B: %b";
            signed int arg = 61276;
            char result[] = "B: 0b1110111101011100";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("two") {
            char fmt[] = "Neg: %b";
            signed int arg = INT_MIN; //-2.147.483.648
            char result[] = "Neg: 0b10000000000000000000000000000000";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("three") {
            char fmt[] = "Neg: %b";
            signed int arg = -1;
            char result[] = "Neg: 0b11111111111111111111111111111111";
                                    
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("four") {
            char fmt[] = "Pos: %b";
            signed int arg = INT_MAX; // 2147483647
            char result[] = "Pos: 0b1111111111111111111111111111111";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
    }
    SECTION("hex") {
        SECTION("one") {
            char fmt[] = "X: %x";
            signed int arg = 61276;
            char result[] = "X: 0xef5c";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("two") {
            char fmt[] = "Neg: %x";
            signed int arg = INT_MIN; //-2.147.483.648
            char result[] = "Neg: 0x80000000";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("three") {
            char fmt[] = "Neg: %x";
            signed int arg = -1;
            char result[] = "Neg: 0xffffffff";
                                    
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
        SECTION("four") {
            char fmt[] = "Pos: %x";
            signed int arg = INT_MAX; // 2147483647
            char result[] = "Pos: 0x7fffffff";
            
            pas.AddFormat(fmt, arg);
            REQUIRE(strcmp(pas.operator const char *(), result) == 0);

            pas.Empty();
        }
    }
    SECTION("skip") {
        char fmt[] = "skip: %%";
        char result[] = "skip: %";
        
        pas.AddFormat(fmt);
        REQUIRE(strcmp(pas.operator const char *(), result) == 0);

        pas.Empty();
    }
}

TEST_CASE("AddFormat: out of bounds", "[Printf]") {
    SECTION("standard 1") {
        CREATE(pas, 4);

        char fmt[] = "ABCDEFGHI";
        pas.AddFormat(fmt);
        
        REQUIRE(pas.GetLength() == 0);
    }
    SECTION("standard 2") {
        CREATE(pas, 8);

        char fmt[] = "ABCDEFGH2";
        pas.AddFormat(fmt);
        
       REQUIRE(pas.GetLength() == 0);
    }

    SECTION("with Specifiers") {
        SECTION("%d") {
            CREATE(pas, 3);

            char fmt[] = "AB%d";
            int arg = -12442;
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%u") {
            CREATE(pas, 3);

            char fmt[] = "AB%u";
            unsigned int arg = 12442;
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%c") {
            CREATE(pas, 2);

            char fmt[] = "AB%c";
            char arg = 'V';
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%s") {
            CREATE(pas, 3);

            char fmt[] = "AB%s";
            char arg[] = "Vasdagds";
            pas.AddFormat(fmt, arg);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%x") {
            CREATE(pas, 3);
            char fmt[] = "AB%x";
            int arg = 0xabcd;
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%b") {
            CREATE(pas, 3);

            char fmt[] = "AB%b";
            int arg = 0b11101010;
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%%") {
            CREATE(pas, 2);

            char fmt[] = "AB%%";
            char arg = 'V';
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("mixed") {
            CREATE(pas, 16);

            char fmt[] = "12 %x 79 %s";
            int arg1 = 0x123;
            char arg2[] = "HASKdha";
            pas.AddFormat(fmt, arg1, arg2);
            
            REQUIRE(pas.GetLength() == 0);
        }
        SECTION("%%") {
            CREATE(pas, 2)

            char fmt[] = "AB%%";
            char arg = 'V';
            pas.AddFormat(fmt);
            
            REQUIRE(pas.GetLength() == 0);
        }
    }
}