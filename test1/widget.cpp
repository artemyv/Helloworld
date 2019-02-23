#include <iostream>

template <typename T>
class Printer {
    T t_;
public:
    Printer(const T& t) :t_(t) {};
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

struct A
{
    A(int n) : a(n) {}
    int a;
};
// Compile with /w15038 to enable the warning
struct B : A
{
    B(int n) : b(n), A(b) {} // warning C5038: data member ‘B::b’ will be initialized after base class ‘A’
    int b;
};