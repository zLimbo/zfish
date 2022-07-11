#include "a.hh"

namespace static_test {
namespace A {
void set_value(int val) {
    auto& value = static_value();
    value = val;
}

void print_value() {
    std::cout << static_value() << '\n';
}
}  // namespace A
}  // namespace static_test