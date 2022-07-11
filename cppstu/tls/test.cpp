#include <string>
#include <iostream>
#include <thread>

struct MyData {
    inline static std::string gName = "global";
    inline static thread_local std::string tName = "tls";
    std::string lName = "local";
    void print(const std::string& msg) const {
        std::cout << msg << '\n';
        std::cout << "- gName: " << gName << '\n';
        std::cout << "- tName: " << tName << '\n';
        std::cout << "- lName: " << lName << '\n';
    }
    static MyData myThreadData;
};

inline thread_local MyData myThreadData;

void foo() {
    myThreadData.print("foo() begin:");
    myThreadData.gName = "thread2 name";
    myThreadData.tName = "thread2 name";
    myThreadData.lName = "thread2 name";
    myThreadData.print("foo() end:");
}

int main() {
    myThreadData.print("main() begin:");
    myThreadData.gName = "thraed1 name";
    myThreadData.tName = "thread1 name";
    myThreadData.lName = "thread1 name";
    myThreadData.print("main() later:");
    std::thread t(foo);
    t.join();
    myThreadData.print("main() end:");

    return 0;
}