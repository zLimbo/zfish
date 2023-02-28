

template <typename T>
struct declval_protector {
    static constexpr bool value = false;
};

template <typename T>
T&& declval() {
    static_assert(declval_protector<T>::value,
                  " decltype 应该只在decltype/sizeof等非求值上下文中使用!");
}

template <typename F, typename... Args>
using InvokeResultOfFunc = decltype(declval<F>()(declval<Args>()...));

struct AFunctionObj {
    double operator()(char, int);
    float operator()(int);
} f;

using T1 = InvokeResultOfFunc<AFunctionObj, char, int>;
using T2 = InvokeResultOfFunc<AFunctionObj, int>;

int main() {
    // declval<AFunctionObj>();
    return 0;
}