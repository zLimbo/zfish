#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream fin("test.sql");
    string sql;
    getline(fin, sql);

    cout << sql << endl;

    int pos = sql.find("ddd");
    sql.erase(pos, 3);
    sql.insert(pos, to_string(12345));

    cout << sql << endl;

    return 0;
}