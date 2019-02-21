//downloaded from https://github.com/catchorg/Catch2/tree/master/single_include/catch2
/*
 *  Catch v2.6.1
 *  Generated: 2019-02-12 19:52:52.262497
 *  ----------------------------------------------------------
 *  This file has been merged from multiple headers. Please don't edit it directly
 *  Copyright (c) 2019 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include "catch.hpp"

//downloaded from https://github.com/eranpeer/FakeIt/tree/master/single_header/catch
/*
 *  FakeIt - A Simplified C++ Mocking Framework
 *  Copyright (c) Eran Pe'er 2013
 *  Generated: 2018-08-17 00:22:40.428924
 *  Distributed under the MIT License. Please refer to the LICENSE file at:
 *  https://github.com/eranpeer/FakeIt
 */

#include "fakeit.hpp" 

using namespace fakeit;

#include <string>

struct InterfaceSample {
    virtual int bar(const std::string&) const = 0;
};
int func_sample(const InterfaceSample& i, const std::string& val)
{
    return i.bar(val);
}

TEST_CASE("Fakeit.Verify", "[Fake][!mayfail]")
{
    Mock<InterfaceSample> mock;
    SECTION("Good")
    {
        When(Method(mock, bar).Using("1")).Return(100);
        REQUIRE(func_sample(mock.get(), "1") == 100);
        Verify(Method(mock, bar).Using("1")).Once();
    }
}
/*
$ TestCatch2.exe - s - r compact
test.cpp(22) : passed: func_sample(mock.get(), "1") == 100 for : 100 == 100
test.cpp(23) : failed: mock.bar(1) with 1 message : 'test.cpp(23): Verification error
    Expected pattern : mock.bar(1)
    Expected matches : exactly 1
    Actual matches : 0
    Actual sequence : total of 1 actual invocations :
  mock.bar()'
      Failed 1 test case, failed 1 assertion.
*/
