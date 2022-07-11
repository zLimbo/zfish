#include "a.hh"
#include "b.hh"

int main() {
    static_test::A::set_value(42);

    static_test::A::print_value();
    static_test::B::print_value();

    static_test::B::set_value(37);

    static_test::A::print_value();
    static_test::B::print_value();

    return 0;
}