
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <getopt.h>
using namespace std;

int main(int argc, char *argv[]) {
    const char *str = "ab:c:";
    int opt = '?';
    while (opt = getopt(argc, argv, str), opt != -1) {
        switch (opt) {
            case 'a':
                cout << 'a' << " " << optind << " " << argv[optind] << endl;
                break;
            case 'b':
                cout << 'b' << " " << argv[optind] << " " << optarg << endl;
                break;
            case 'c':
                cout << 'c' << " " << argv[optind] << " " << optarg << endl;
                break;
            default:
                cout << char(opt) << " " << opterr << endl;
        }
    }
    return 0;
}