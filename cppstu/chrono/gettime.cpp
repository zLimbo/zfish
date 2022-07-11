#include <string>
#include <ctime>
#include <chrono>
using namespace std;

std::string get_date_time() {
    auto to_string =
        [](const std::chrono::system_clock::time_point& t) -> std::string {
        auto as_time_t = std::chrono::system_clock::to_time_t(t);
        struct tm tm;
#if defined(WIN32) || defined(_WINDLL)
        localtime_s(
            &tm, &as_time_t);  // win api，线程安全，而std::localtime线程不安全
#else
        localtime_r(&as_time_t, &tm);  // linux api，线程安全
#endif

        std::chrono::milliseconds ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                t.time_since_epoch());
        char buf[128];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d %03lld ",
                 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                 tm.tm_min, tm.tm_sec, ms.count() % 1000);
        return buf;
    };

    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    return to_string(t);
}