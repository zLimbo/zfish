
template <typename T, typename U>
struct Pair {
    Pair();
    // Pair(T, U);

    template <typename A, typename B>
    Pair(A&&, B&&) {}
};

// 17, 推导规则
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

Pair foo{1, 2};

int main() {
    return 0;
}