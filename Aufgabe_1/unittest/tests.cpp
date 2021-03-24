#include "catch.hpp"

#include "OptChecker.h"

TEST_CASE("OptChecker: isVariable(..)", "[OptChecker]") {
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

TEST_CASE("OptChecker: is")