#include <mutex>
#include <thread>
#include <exception>

template <typename T>
class Guarded
{
    T _value;
    std::mutex _m{};
    std::thread::id _aquired{};
public:
	_When_(true, _Acquires_lock_(this->_m))
    void lock()  { _m.lock(); _aquired = std::this_thread::get_id(); }
    bool try_lock() {
        if (_m.try_lock()) { _aquired = std::this_thread::get_id(); return true; }
        return false;
    }
	_When_(true, _Releases_lock_(this->_m))
	void unlock()  { _aquired = std::thread::id{}; _m.unlock(); }
    T& get()  //[[expects(_m.aquired)]] -> locked on current thread -> see implementation by Hutter on cppcon 2018
    {
        if (_aquired != std::this_thread::get_id())
        {
            throw std::runtime_error("Precodintions not met");
        }
        return _value; //returned reference cannot be used after unlock()
    }
    explicit Guarded(T t) noexcept : _value(t) {}
};