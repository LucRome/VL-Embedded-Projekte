#include "catch.hpp"

#include "LiteralChecker.h"
#include "OptParser.h"

//////////////////////////////////////////////////////////
//          LiteralChecker
//////////////////////////////////////////////////////////

TEST_CASE("OptChecker::isVariable(..)", "[OptChecker]")
{
    SECTION("Correct:")
    {
        char str1[] = "-a";
        char str2[] = "-z";
        char str3[] = "-A";
        char str4[] = "-Z";

        REQUIRE_NOTHROW(LiteralChecker::isVariable(str1));
        REQUIRE_NOTHROW(LiteralChecker::isVariable(str2));
        REQUIRE_NOTHROW(LiteralChecker::isVariable(str3));
        REQUIRE_NOTHROW(LiteralChecker::isVariable(str4));
    }
    SECTION("Incorrect:")
    {
        char str1[] = "-0";
        char str2[] = "-[";
        char str3[] = "_a";

        REQUIRE_FALSE(LiteralChecker::isVariable(str1));
        REQUIRE_FALSE(LiteralChecker::isVariable(str2));
        REQUIRE_FALSE(LiteralChecker::isVariable(str3));
    }
}

TEST_CASE("OptChecker::isValue(..)", "[OptChecker]")
{
    SECTION("Correct:")
    {
        char str1[] = "hel0";
        char str2[] = "023ka";

        REQUIRE_NOTHROW(LiteralChecker::isValue(str1));
        REQUIRE_NOTHROW(LiteralChecker::isValue(str2));
    }
    SECTION("Incorrect:")
    {
        char str1[] = "-as";
        char str2[] = "as vde";
        char str3[] = "l_";

        REQUIRE_FALSE(LiteralChecker::isValue(str1));
        REQUIRE_FALSE(LiteralChecker::isValue(str2));
        REQUIRE_FALSE(LiteralChecker::isValue(str3));
    }
}

TEST_CASE("OptChecker::isEquals(..)", "[OptChecker]")
{
    SECTION("Correct:")
    {
        char str1[] = "=";
        char str2[] = " ";

        REQUIRE_NOTHROW(LiteralChecker::isEquals(str1));
        REQUIRE_NOTHROW(LiteralChecker::isEquals(str2));
    }
    SECTION("Incorrect:")
    {
        char str1[] = "";
        char str2[] = "x";

        REQUIRE_FALSE(LiteralChecker::isEquals(str1));
        REQUIRE_FALSE(LiteralChecker::isEquals(str2));
    }
}

TEST_CASE("OptChecker::EOA(..)", "[OptChecker]")
{
    SECTION("Correct:")
    {
        char str1[] = "a";
        char *eoa = str1 + 1;
        REQUIRE_NOTHROW(LiteralChecker::EOA(eoa));
    }
    SECTION("Incorrect:")
    {
        char str1[] = "1";
        REQUIRE_FALSE(LiteralChecker::EOA(str1));
    }
}

// Maybe also test private fkt. of OptChecker

//////////////////////////////////////////////////////////
//          CmdLineOptParser
//////////////////////////////////////////////////////////

TEST_CASE("OptParser::Parse(..)", "[OptParser]")
{
    CmdLineOptParser parser = CmdLineOptParser();

    //All argv start with "progname" (like real program)
    SECTION("Correct:")
    {
        {
            char arg0[] = "progname";
            char arg1[] = "-x";
            char arg2[] = "-y";
            char arg3[] = "val";
            char *argv[] = {arg0, arg1, arg2, arg3};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_NOTHROW(parser.Parse(argc, argv));
        }
        {
            char arg0[] = "progname";
            char arg1[] = "-L";
            char arg2[] = "90a";
            char arg3[] = "-Z";
            char arg4[] = "-K";
            char *argv[] = {arg0, arg1, arg2, arg3, arg4};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_NOTHROW(parser.Parse(argc, argv));
        }
        {
            char arg0[] = "progname";
            char arg1[] = "-L 90a";
            char arg2[] = "-Z=80";
            char arg3[] = "-K";
            char *argv[] = {arg0, arg1, arg2, arg3};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_NOTHROW(parser.Parse(argc, argv));
        }
    }
    SECTION("Incorrect:")
    {
        {
            //Error: argv[1]
            char arg0[] = "progname";
            char arg1[] = "ld";
            char arg2[] = "kv";
            char arg3[] = "-x";
            char *argv[] = {arg0, arg1, arg2, arg3};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_FALSE(parser.Parse(argc, argv));
        }
        {
            //Error: argv[2]
            char arg0[] = "progname";
            char arg1[] = "-x";
            char arg2[] = "__AB";
            char *argv[] = {arg0, arg1, arg2};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_FALSE(parser.Parse(argc, argv));
        }
        {
            //Error: argv[1]
            char arg0[] = "progname";
            char arg1[] = "-0";
            char arg2[] = "AB";
            char *argv[] = {arg0, arg1, arg2};
            int argc = sizeof(argv) / sizeof(argv[0]);
            REQUIRE_FALSE(parser.Parse(argc, argv));
        }
    }
}