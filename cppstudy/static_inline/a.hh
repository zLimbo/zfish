#ifndef A_HH
#define A_HH

#include <iostream>

namespace static_test {
static int& static_value()  // (!*!) Or change this to inline
{
    static int value = -1;
    return value;
}

namespace A {
void set_value(int val);
void print_value();
}  // namespace A
}  // namespace static_test

#endif