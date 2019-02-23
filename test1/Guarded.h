#include <mutex>
#include <thread>
#include <exception>

template <typename T>
class Guarded
{
    T _value;
    std::mutex _m;
    std::thread::id _aquired;
public:
    void lock() { _m.lock(); _aquired = std::this_thread::get_id();}
    bool try_lock() {
        if (_m.try_lock()) { _aquired = std::this_thread::get_id(); return true; }
        return false;
    }
    void unlock() { _aquired = std::thread::id{}; _m.unlock(); }
    T& get()  //[[expects(_m.aquired)]] -> locked on current thread -> see implementation by Hutter on cppcon 2018
    {
        if (_aquired != std::this_thread::get_id()) throw std::runtime_error("Precodintions not met");
        return _value; //returned reference cannot be used after unlock()
    }
    explicit Guarded(T t) : _value(t), _m{}, _aquired{} {}
};