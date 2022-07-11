#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main() {
    auto cwd = fs::current_path();
    cout << cwd << endl;

    // fs::create_directories("a/b/c");
    fs::remove_all("a");
    puts("abc");
    fputs("abc", stdout);

    return 0;
}