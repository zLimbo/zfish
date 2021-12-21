#include <httplib.h>
#include <json/json.h>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    httplib::Client cli("192.168.6.104", 1337);
    ifstream fin("signed_data.txt");
    string signed_data;
    getline(fin, signed_data);

    Json::Value value;
    value["jsonrpc"] = "2.0";
    value["method"] = "sendRawTransaction";
    value["id"] = 1;
    value["params"].append(signed_data);

    Json::StreamWriterBuilder wbuilder;
    string body = Json::writeString(wbuilder, value);
    cout << "body: " << body << endl;

    if (auto res = cli.Post("/", body, "application/json")) {
        cout << "status: " << res->status << endl;
        cout << "content-type: " << res->get_header_value("Content-Type")
             << endl;
        cout << "body: " << res->body << endl;
    } else {
        cout << "error code: " << res.error() << std::endl;
    }

    return 0;
}