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