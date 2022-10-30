#include <random>

namespace zl {

constexpr int kMaxLevel = 15;

template <typename T>
class SkipList;

template <typename T>
class SkipNode {
    friend SkipList<T>;

public:
    SkipNode(const T& data, int level = 0)
        : data_(data), level_(level), next_(new SkipList<T>*[kMaxLevel]) {
        for (int i = 0; i < kMaxLevel; ++i) {
            next_[i] = nullptr;
        }
    }

    ~SkipNode() { delete[] next_; }

private:
    T data_;
    int level_;
    SkipNode<T>** next_;
};

template <typename T>
class SkipList {
public:
    SkipList() {}

    int RandomLevel() const {
        static std::default_random_engine e(0);
        static std::uniform_real_distribution<double> u(0, 1);
        int level = 0;
        while (u(e) < 0.5 && level < kMaxLevel) {
            ++level;
        }
        return level;
    }

    void Append(const T& e) {
        int level = RandomLevel();
        SkipNode<T>* sn = new SkipNode<T>(e, level);

        SkipNode<T>* pre = &head_;
        for (int cur_level = head_.level_; cur_level >= 0; --cur_level) {
            while (pre->next_[cur_level] && pre->next_[cur_level].data_);
        }

        for (; head_.level_ < level; ++head_.level_) {
            head_.next_[head_.level_ + 1] = sn;
        }
    }

private:
    int size_;
    SkipNode<T> head_;
};
}  // namespace zl