#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <chrono>
#include <optional>
#include "Guarded.h"


extern "C" struct MY_OBJ_HANDLE_DUMMY
{
    char _unused;
};
using MY_OBJ_HANDLE = struct MY_OBJ_HANDLE_DUMMY*;

class MyClass : public MY_OBJ_HANDLE_DUMMY
{
    Guarded<int> m_value{ -1 };
public:
    void SetGet(bool bSet, int& value)
    {
        std::lock_guard lock(m_value);
        if (bSet)
        {
            m_value.get() = value;
        }
        else
        {
            value = m_value.get();
        }
    }
};

extern "C" MY_OBJ_HANDLE CreateMyClass()
{
    return static_cast<MY_OBJ_HANDLE>(new MyClass);
}
extern "C" void DestructMyClass(MY_OBJ_HANDLE h)
{
    delete static_cast<MyClass*>(h);
}

extern "C" void SetValue(MY_OBJ_HANDLE h, int value)
{
    auto c = static_cast<MyClass*>(h);
    c->SetGet(true, value);
}

extern "C" int GetValue(MY_OBJ_HANDLE h)
{
    auto c = static_cast<MyClass*>(h);
    int value;
    c->SetGet(false, value);
    return value;
}


int main()
{
    auto h = CreateMyClass();

    //Do stuff with h
    SetValue(h, 123);
    int value = GetValue(h);
    std::cout << " read " << value << "\n";


    DestructMyClass(h);

}
