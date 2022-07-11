
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <json/json.h>
using namespace std;

int main() {
    Json::Value json;
    json['a'] = 10;
    cout << json << endl;
    return 0;
}