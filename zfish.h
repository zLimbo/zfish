#ifndef ZFISH_H
#define ZFISH_H

#include <string_view>
#include <vector>

namespace zfish {

using std::string_view;
using std::vector;

vector<string_view> split(string_view sv, string_view delim = " ") {
    vector<string_view> res;
    size_t b = sv.find_first_not_of(delim);
    size_t e = sv.find_first_of(delim, b);
    while (b != string_view::npos) {
        res.push_back(sv.substr(b, e - b));
        b = sv.find_first_not_of(delim, e);
        e = sv.find_first_of(delim, b);
    }
    return res;
}

}  // namespace zfish

#endif  // ZFISH_H