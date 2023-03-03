#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace fmt;

// 谓词 predicate
static_assert(is_integral<int>::value);
static_assert(!is_integral<float>::value);

// variable template
template <typename T>
constexpr bool is_integral_v = is_integral<T>::value;
template <typename T>
constexpr bool is_class_v = is_class<T>::value;
template <char c>
constexpr bool is_digit = (c >= '0' && c <= '9');

// fib
template <size_t N>
constexpr size_t fibonacci = fibonacci<N - 1> + fibonacci<N - 2>;
template <>
constexpr size_t fibonacci<0> = 0;
template <>
constexpr size_t fibonacci<1> = 1;

template <size_t N>
constexpr double golden_ratio = fibonacci<N + 1> * 1.0 / fibonacci<N>;

// 类型转换
static_assert(is_same_v<typename remove_const<const int>::type, int>);
static_assert(is_same_v<typename remove_const<int>::type, int>);
static_assert(is_same_v<typename add_const<int>::type, const int>);
static_assert(is_same_v<typename add_pointer<int**>::type, int***>);
static_assert(is_same_v<typename decay<int[5][6]>::type, int(*)[6]>);



int main() {
    println("is digit: {}", is_digit<'c'>);
    println("fib(30) = {}", fibonacci<30>);
    println("golden_ratio<20> = {:.10f}", golden_ratio<20>);
    println("golden_ratio<30> = {:.10f}", golden_ratio<30>);
    return 0;
}