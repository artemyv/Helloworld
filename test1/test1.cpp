#include <future>
#include <iostream>
#include <string>
#include <vector>

std::future<int> test()
{
    struct Return
    {
        std::string msg;
        int code = -1;
        std::vector<uint8_t> value;
    };
    std::promise<Return> ret_val;
    auto local = ret_val.get_future();
    auto func = [](std::promise<Return>&& ret_val) -> int
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ret_val.set_value({ "Hello", 5, {1,2,3,4,5} });
        return 0;
    };

    auto task = std::async(std::launch::async, func, std::move(ret_val));
    if (local.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready)
    {
        auto i = local.get();
        std::cout << "call local=" << i.msg << "\n";
    }

    return task;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    auto res = test();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start);
    std::cout << "call finished: " << duration.count() << "ms\n";
    res.wait_for(std::chrono::milliseconds(2000));
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start);
    std::cout << "wait finished: " << duration.count() << "ms\n";

}
