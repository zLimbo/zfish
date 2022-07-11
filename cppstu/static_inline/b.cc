#include "b.hh"

#include "a.hh"

namespace static_test {
namespace B {
void set_value(int val) {
    auto& value = static_value();
    value = val;
}

void print_value() {
    std::cout << static_value() << '\n';
}
}  // namespace B
}  // namespace static_test