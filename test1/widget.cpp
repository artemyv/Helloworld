#include <iostream>

template <typename T>
class Printer {
    T t_;
public:
    explicit Printer(const T& t) :t_(t) {};
    std::ostream& print(std::ostream& o) { return o << t_ << ','; }
};

class Driver {
public:
    template <typename T>
    std::ostream& usePrinter(std::ostream& o, Printer <T>& foo);
};

template <typename T>
std::ostream& Driver::usePrinter(std::ostream& o, Printer <T>& foo)
{
    return foo.print(o);
}
template <class T, class U>
void test(T t, U u)
{
    if (sizeof(T) < sizeof(U))
        // warning C4127 : conditional expression is constant
        // note : consider using ‘if constexpr’ statement instead
    {

    }
}


