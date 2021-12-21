#include "json.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    nlohmann::json j;
    j["A"] = 3;
    j["B"] = 4;
    string s = j.dump();
    cout << s << endl;
    return 0;
}