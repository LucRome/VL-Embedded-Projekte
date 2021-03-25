#include "catch.hpp"

#include "OptChecker.h"

//////////////////////////////////////////////////////////
//          CmdLineOptChecker
//////////////////////////////////////////////////////////

TEST_CASE("OptChecker::isVariable(..)", "[OptChecker]") {
    SECTION("Correct:") {
        char str1[] = "-a";
        char str2[] = "-z";
        char str3[] = "-A";
        char str4[] = "-Z";
        
        REQUIRE(CmdLineOptChecker::isVariable(str1));
        REQUIRE(CmdLineOptChecker::isVariable(str2));
        REQUIRE(CmdLineOptChecker::isVariable(str3));
        REQUIRE(CmdLineOptChecker::isVariable(str4));
    }
    SECTION("Incorrect:") {
        char str1[] = "-0";
        char str2[] = "-[";
        char str3[] = "_a";

        REQUIRE_FALSE(CmdLineOptChecker::isVariable(str1));
        REQUIRE_FALSE(CmdLineOptChecker::isVariable(str2));
        REQUIRE_FALSE(CmdLineOptChecker::isVariable(str3));
    }
}

TEST_CASE("OptChecker::isValue(..)", "[OptChecker]") {
    SECTION("Correct:") {
        char str1[] = "hel0";
        char str2[] = "023ka";

        REQUIRE(CmdLineOptChecker::isValue(str1));
        REQUIRE(CmdLineOptChecker::isValue(str2));
    }
    SECTION("Incorrect:") {
        char str1[] = "-as";
        char str2[] = "as vde";
        char str3[] = "l_";

        REQUIRE_FALSE(CmdLineOptChecker::isValue(str1));
        REQUIRE_FALSE(CmdLineOptChecker::isValue(str2));
        REQUIRE_FALSE(CmdLineOptChecker::isValue(str3));
    }
}

TEST_CASE("OptChecker::isEquals(..)", "[OptChecker]") {
    SECTION("Correct:") {
        char str1[] = "=";
        char str2[] = " ";

        REQUIRE(CmdLineOptChecker::isEquals(str1));
        REQUIRE(CmdLineOptChecker::isEquals(str2));
    }
    SECTION("Incorrect:") {
        char str1[] = "";
        char str2[] = "x";

        REQUIRE_FALSE(CmdLineOptChecker::isEquals(str1));
        REQUIRE_FALSE(CmdLineOptChecker::isEquals(str2));
    }
}

TEST_CASE("OptChecker::EOA(..)", "[OptChecker]") {
    SECTION("Correct:") {
        char str1[] = "a";
        char* eoa = str1 + 1;
        REQUIRE(CmdLineOptChecker::EOA(eoa));
    }
    SECTION("Incorrect:") {
        char str1[] = "1";
        REQUIRE_FALSE(CmdLineOptChecker::EOA(str1));
    }
}

// Maybe also test private fkt. of OptChecker

//////////////////////////////////////////////////////////
//          CmdLineOptParser
//////////////////////////////////////////////////////////