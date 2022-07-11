#define FMT_HEADER_ONLY
#include <fmt/printf.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);

    auto future1 = pool.put([] { return 3; });
    auto future2 = pool.put([] { return "abcd"; });

    fmt::print("f1: {}\n", future1.get());
    fmt::print("f2: {}\n", future2.get());

    pool.close();
    return 0;
}
