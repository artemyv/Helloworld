#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <list>

template<class Func, class ...Args>
std::pair<bool,bool> wrapper(std::list<std::future<int>>& peding, Func f, Args... args) {
    bool bAsync = false;
    if (bAsync)
    {
        auto task = std::async(std::launch::async, f, std::forward<Args>(args)...);
        if (task.wait_for(std::chrono::milliseconds(100)) == std::future_status::ready)
        {
            return std::make_pair(true, true);
        }
        peding.emplace_back(std::move(task));
        return std::make_pair(false, true);
    }
    else
    {
        return std::make_pair(true, false); //Sync - call function outside wrapper
    }
}
void test(std::list<std::future<int>>& peding)
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
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        ret_val.set_value({ "Hello", 5, {1,2,3,4,5} });
        return 0;
    };
    auto result = wrapper(peding, func, std::move(ret_val));
    if (!result.second)
    {
        std::cout << "making sync call1\n";
        return;
    }

    if (local.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
    {
        auto i = local.get();
        std::cout << "call1 local=" << i.msg << "\n";
    }

    return;
}

void test1(std::list<std::future<int>>& peding)
{
    auto func = []() -> int
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 0;
    };
    auto result = wrapper(peding, func);
    if (!result.second)
    {
        std::cout << "making sync call2\n";
        return;
    }

    if (result.first)
    {
        std::cout << "async call2 succeded\n";
    }

    return;
}

int main()
{
    std::list<std::future<int>> peding;
    auto start = std::chrono::steady_clock::now();
    test(peding);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start);
    std::cout << "call finished: " << duration.count() << "ms\n";
    test1(peding);
    std::cout << "call2 finished: " << duration.count() << "ms\n";

    for (auto& p : peding)
    {
        p.wait();
    }
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start);
    std::cout << "wait finished: " << duration.count() << "ms\n";

}
