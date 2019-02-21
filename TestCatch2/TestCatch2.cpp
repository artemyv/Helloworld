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
TEST_CASE("Fakeit", "[Fake]")
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

TEST_CASE("Fakeit2", "[Fake]")
{
    Mock<SomeInterface> mock;
    // Stub a method to return a value once
    SECTION("Good")
    {
        int  called = 0;
        When(Method(mock, bar).Using("1")).Do([&](const std::string& p) 
        {
            called++;
            WARN("bar(" + p + ") called");
            return 100; 
        });
        REQUIRE(func2(mock.get(), "1") == 100);
        REQUIRE(called == 1);
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


namespace Catch {
    class TerseReporter : public StreamingReporterBase<TerseReporter>
    {
    public:
        TerseReporter(ReporterConfig const& _config)
            : StreamingReporterBase(_config)
        {
        }

        static std::string getDescription()
        {
            return "Terse output";
        }

        virtual void assertionStarting(AssertionInfo const&) {}
        virtual bool assertionEnded(AssertionStats const& stats) {
            if (!stats.assertionResult.succeeded()) {
                const auto location = stats.assertionResult.getSourceInfo();
                std::cout << location.file << "(" << location.line << ") error\n"
                    << "\t";

                switch (stats.assertionResult.getResultType()) {
                case ResultWas::DidntThrowException:
                    std::cout << "Expected exception was not thrown";
                    break;

                case ResultWas::ExpressionFailed:
                    std::cout << "Expression is not true: " << stats.assertionResult.getExpandedExpression();
                    break;

                case ResultWas::Exception:
                    std::cout << "Unexpected exception";
                    break;

                default:
                    std::cout << "Test failed";
                    break;
                }

                std::cout << std::endl;
            }

            return true;
        }

        void sectionStarting(const SectionInfo& info) override
        {
            ++sectionNesting_;

            StreamingReporterBase::sectionStarting(info);
        }

        void sectionEnded(const SectionStats& stats) override
        {
            if (--sectionNesting_ == 0) {
                totalDuration_ += stats.durationInSeconds;
            }

            StreamingReporterBase::sectionEnded(stats);
        }

        void testRunEnded(const TestRunStats& stats) override
        {
            if (stats.totals.assertions.allPassed()) {
                std::cout << "SUCCESS (" << stats.totals.testCases.total() << " tests, "
                    << stats.totals.assertions.total() << " assertions, "
                    << static_cast<int> (totalDuration_ * 1000) << " ms)";
            }
            else {
                std::cout << "FAILURE (" << stats.totals.assertions.failed << " out of "
                    << stats.totals.assertions.total() << " failed, "
                    << static_cast<int> (totalDuration_ * 1000) << " ms)";
            }

            std::cout << std::endl;

            StreamingReporterBase::testRunEnded(stats);
        }

    private:
        int sectionNesting_ = 0;
        double totalDuration_ = 0;
    };

    CATCH_REGISTER_REPORTER("terse", TerseReporter)
}