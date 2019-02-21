#include  <future>
#include <iostream>


std::future<int> test()
{
    std::promise<int> ret_val;
    auto local = ret_val.get_future();
    auto func = [](std::promise<int>&& ret_val) -> int
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ret_val.set_value(5);
        return 0;
    };

    auto task = std::async(std::launch::async, func, std::move(ret_val));
    task.wait_for(std::chrono::milliseconds(100));
    if (local.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
    {
        auto i = local.get();
        std::cout << "call local=" << i << "\n";
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


