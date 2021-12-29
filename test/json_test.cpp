#include "hlib/json.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace nlohmann;

int main() {
    json j;

    cout << j.dump() << endl;

    j["A"] = 3;
    j["B"] = 4;
    cout << (j.type() == json::value_t::object) << endl;
    string s = j.dump();
    cout << s << endl;

    json j2 = j["C"];

    cout << j.dump() << endl;
    cout << j2.dump() << endl;

    return 0;
}