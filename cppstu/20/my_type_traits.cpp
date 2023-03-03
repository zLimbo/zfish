
// #include <type_traits>

#include <stddef.h>

#include <cmath>
#include <limits>
#include <tuple>
#include <type_traits>
#include <vector>

namespace my_type_traits {

template <typename T, T v>
struct integral_constant {
    using type = integral_constant;
    using value_type = T;
    static constexpr bool value = v;
};

using Two = integral_constant<int, 2>;
using Four = integral_constant<int, 4>;
static_assert(Two::value * Two::value == Four::value);

template <bool v>
using bool_constant = integral_constant<bool, v>;

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

// struct false_type {
//     static constexpr bool value = false;
// };
// struct true_type {
//     static constexpr bool value = true;
// };

template <typename T>
struct is_floating_point : false_type {};
template <>  // 全特化
struct is_floating_point<float> : true_type {};
template <>
struct is_floating_point<double> : true_type {};
template <>
struct is_floating_point<long double> : true_type {};

static_assert(is_floating_point<double>::value);

template <typename T, typename U>
struct is_same : false_type {};
template <typename T>
struct is_same<T, T> : true_type {};  // 偏特化
template <typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

static_assert(is_same_v<int, int>);
static_assert(!is_same_v<int, double>);

template <typename T>
struct remove_const {
    using type = T;
};
template <typename T>
struct remove_const<const T> {
    using type = T;
};

static_assert(is_same_v<remove_const<const int>::type, int>);

template <bool v, typename Then, typename Else>
struct conditional {
    using type = Then;
};
template <typename Then, typename Else>
struct conditional<false, Then, Else> {
    using type = Else;
};
template <bool v, typename Then, typename Else>
using conditional_t = typename conditional<v, Then, Else>::type;

static_assert(is_same_v<conditional_t<false, int, double>, double>);

// 类型自省
// 萃取数组组成
template <typename T>
struct array_size;
template <typename E, size_t N>
struct array_size<E[N]> {
    using value_type = E;
    static constexpr size_t len = N;
};

static_assert(is_same_v<array_size<int[5]>::value_type, int>);
static_assert(array_size<int[5]>::len == 5);

// 萃取函数组成
template <typename F>
struct function_trait;
template <typename Ret, typename... Args>
struct function_trait<Ret(Args...)> {
    using result_type = Ret;
    using args_type = std::tuple<Args...>;
    static constexpr size_t num_of_args = sizeof...(Args);
    template <size_t I>
    using arg = std::tuple_element_t<I, args_type>;
};

using F = void(int, float, std::vector<char>);
static_assert(is_same_v<function_trait<F>::result_type, void>);
static_assert(function_trait<F>::num_of_args == 3);
static_assert(is_same_v<function_trait<F>::arg<2>, std::vector<char>>);

// enable_if 元函数
template <bool, typename = void>
struct enable_if {};
template <typename T>
struct enable_if<true, T> {
    using type = T;
};
template <bool Cond, typename T = void>
using enable_if_t = typename enable_if<Cond, T>::type;

static_assert(is_same_v<enable_if<true>::type, void>);

// 实现数值判等
template <typename T, enable_if_t<std::is_integral_v<T>>* = nullptr>
bool numEq(T lhs, T rhs) {
    return lhs == rhs;
}
template <typename T, enable_if_t<is_floating_point<T>::value>* = nullptr>
bool numEq(T lhs, T rhs) {
    return std::fabs(lhs - rhs) < std::numeric_limits<T>::epsilon();
}

}  // namespace my_type_traits
