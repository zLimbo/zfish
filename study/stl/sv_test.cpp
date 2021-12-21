#define FMT_HEADER_ONLY
#include <fmt/printf.h>

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

int main() {
    std::string_view sv1 = "0123456";
    std::string_view sv2 = sv1.substr(5, 10);
    print("sv1.size = {}, sv2.size = {}\n", sv1.size(), sv2.size());
    std::string_view sv3(string("abcdefg"));
    char *s = strdup(sv3.data());
    std::string_view sv4 = s;

    print("{}\n", "\u20ac");
    printf("%s\n", "\u20ac");

    std::string_view sv5 = "\u4F60\u597D";
    for (int i = 0; i < sv5.size(); ++i) {
        printf("%x ", (unsigned char)sv5.data()[i]);
    }
    print("\n");
    printf("%s\n", sv5);
    print("{}\n", sv5);
    return 0;
}