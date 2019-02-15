#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "fakeit.hpp" 

using namespace fakeit;

//#include <utility.h>
#include <string>

struct SomeInterface {
    virtual int foo(std::string) const = 0;
    virtual int bar(const std::string&) const = 0;
    virtual int fb(std::string&) const = 0;
};
int func1(const SomeInterface& i, std::string val)
{
    return i.foo(val);
}
int func2(const SomeInterface& i, const std::string& val)
{
    return i.bar(val);
}
int func3(const SomeInterface& i, std::string& val)
{
    val += "1";
    return i.fb(val);
}
TEST_CASE("Fakeit", "[Fake][.]")
{
    Mock<SomeInterface> mock;
    // Stub a method to return a value once
    When(Method(mock, foo)).Return(-1);
    When(Method(mock, foo).Using("1")).Return(100);
    SECTION("Good")
    {
        REQUIRE(func1(mock.get(), "1") == 100);
    }
    SECTION("Bad")
    {
        REQUIRE(func1(mock.get(), "2") == -1);
    }
}

TEST_CASE("Fakeit2", "[Fake][.]")
{
    Mock<SomeInterface> mock;
    // Stub a method to return a value once
    When(Method(mock, bar)).Return(-1);
    When(Method(mock, bar).Using("1")).Return(100);
    SECTION("Good")
    {
        REQUIRE(func2(mock.get(), "1") == 100);
    }
    SECTION("Bad")
    {
        REQUIRE(func2(mock.get(), "2") == -1);
    }
}

TEST_CASE("Fakeit3", "[Fake]")
{
    Mock<SomeInterface> mock;
    
    When(Method(mock, fb)).Return(3_Times(-1)); //this should be first for some reason

    When(Method(mock, fb).Using("111")).Return(200);
    When(Method(mock, fb).Using("11")).Return(2_Times(100));
    When(Method(mock, fb).Using("1111")).Return(300);

    SECTION("Good")
    {
        std::string data = "1";
        std::string data2 = "2";
        REQUIRE(func3(mock.get(), data2) == -1);
        REQUIRE(func3(mock.get(), data) == 100);
        REQUIRE(func3(mock.get(), data2) == -1);
        data = "1";
        REQUIRE(func3(mock.get(), data) == 100);
        REQUIRE(func3(mock.get(), data2) == -1);
        REQUIRE(func3(mock.get(), data) == 200);
    }
}
