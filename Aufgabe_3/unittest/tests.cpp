#include "catch.hpp"

# include "PreAllocString.h"
#include <cstring>

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
            printf("operator=");
            CREATE(pas, 7);
            char rhs = 'a';
            pas=rhs;
            printf("pas: %s", pas.operator const char *());
            REQUIRE(pas[0] == rhs);
            REQUIRE(pas[1] == '\0');
        }
        {
            printf("operator= , 2");
            CREATE(pas, 7);

            char rhs[] = "ABCDEF";
            const char* rhs_ptr = rhs;
            pas=rhs_ptr;
            REQUIRE(strcmp(pas.operator const char *(), rhs) == 0);
        }
        {
            printf("operator= , 3");

            CREATE(pas, 7);
            
            char rhs[] = "ABCDEF";
            char * const rhs_ptr = rhs;
            printf("operator= , 4");

            pas=rhs_ptr;
            REQUIRE(strcmp(pas.operator const char *(), rhs) == 0);
        }
    }

    SECTION("operator+=, addWhiteSpace") {
        printf("\n\n operator+=, addWhiteSpace \n");
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
            printf("\n += %s \n", rhs_ptr);
            pas += rhs_ptr;
            printf("| %s |", pas.operator const char *());
            REQUIRE(strcmp(pas.operator const char *(), res) == 0);
        }
    }
}

TEST_CASE("Error") {
    SECTION("operator=") {
        CREATE(pas, 5);
        {
            printf("\n operator=, 1\n");
            char rhs[] = "ABCDEFG";
            const char * rhs_ptr = rhs;
            pas = rhs_ptr;
            REQUIRE(pas.GetLength() == 0);
            for(int i = 0; i < 5; i++) {
                REQUIRE(pas[i] == '\0');
            }
        }
        {
            char rhs[] = "ABCDEF";
            char * const rhs_ptr = rhs;
            pas = rhs_ptr;
            int i = pas.size;
            printf("size: %i", i);
            printf("%s", pas.operator const char *());
            REQUIRE(pas.GetLength() == 0);
            for(int i = 0; i < 5; i++) {
                REQUIRE(pas[i] == 0);
            }
        }
    }
    SECTION("operator+=") {
        {
            CREATE(pas, 5);
            for(int i = 0; i < 6; i++) { //leaves no place for '\0'
                pas += 'a';
            }
            REQUIRE(pas.GetLength() == 0);
            for(int i = 0; i < 6; i++) { //leaves no place for '\0'
                REQUIRE(pas[i] == 0);
            }
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
            for(int i = 0; i < 8; i++) { //leaves no place for '\0'
                REQUIRE(pas[i] == 0);
            }
        }
    }
}