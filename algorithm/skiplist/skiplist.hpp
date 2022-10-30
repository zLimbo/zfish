#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
namespace zfish {

template <typename T>
struct SkipListNode {
    SkipListNode(const T &val, int level)
        : val(val), level(level), nexts(new SkipListNode *[level]) {
        for (int i = 0; i < level; ++i) {
            nexts[i] = nullptr;
        }
    }

    SkipListNode(int level) : level(level), nexts(new SkipListNode *[level]) {
        for (int i = 0; i < level; ++i) {
            nexts[i] = nullptr;
        }
    }

    ~SkipListNode() {
        delete[] nexts;
    }

    T val;
    int level;
    SkipListNode **nexts;
};

template <typename T>
class SkipList {
    using Node = SkipListNode<T>;

public:
    SkipList() : max_level_(0), head_(new Node(1)) {}

    ~SkipList() {
        clear();
        delete head_;
    }

    void clear() {
        while (head_ != nullptr) {
            Node *it = head_;
            head_ = it->nexts[0];
            delete it;
        }
        head_ = new Node(1);
        max_level_ = 0;
    }

    bool Insert(const T &x) {
        assert(head_ != nullptr);
        if (Find(x) != nullptr) {
            return false;
        }
        Node *node = head_;
        int level = RandomLevel();
        if (level > max_level_) {
            level = ++max_level_;
            // 更新head节点
            Node *old_head = head_;
            head_ = new Node(max_level_);
            for (int i = 0; i < max_level_ - 1; ++i) {
                head_->nexts[i] = old_head->nexts[i];
            }
            delete old_head;
        }
        Node *new_node = new Node(x, level);
        Node *prev = head_;
        // 纵向移动
        for (int i = max_level_ - 1; i >= 0; --i) {
            // 横向移动
            while (prev->nexts[i] != nullptr && prev->nexts[i]->val <= x) {
                prev = prev->nexts[i];
            }
            if (i < level) {
                assert(prev != nullptr);
                new_node->nexts[i] = prev->nexts[i];
                prev->nexts[i] = new_node;
            }
        }
        return true;
    }

    Node *Find(const T &x) {
        assert(head_ != nullptr);
        Node *prev = head_;
        // 纵向移动
        for (int i = max_level_ - 1; i >= 0; --i) {
            // 横向移动
            while (prev->nexts[i] != nullptr) {
                if (prev->nexts[i]->val == x) {
                    return prev->nexts[i];
                }
                if (prev->nexts[i]->val > x) {
                    break;
                }
                prev = prev->nexts[i];
            }
        }
        return nullptr;
    }

    bool Erase(const T &x) {
        assert(head_ != nullptr);
        Node *prev = head_;
        Node *hot = nullptr;
        for (int i = max_level_ - 1; i >= 0; --i) {
            while (prev->nexts[i] != nullptr) {
                if (prev->nexts[i]->val == x) {
                    hot = prev->nexts[i];
                    prev->nexts[i] = prev->nexts[i]->nexts[i];
                    break;
                }
                if (prev->nexts[i]->val > x) {
                    break;
                }
                prev = prev->nexts[i];
            }
        }
        if (hot == nullptr) {
            return false;
        }
        delete hot;
        return true;
    }

    void Print() const {
        std::cout << "================================" << std::endl;
        int count = 0;
        for (Node *it = head_->nexts[0]; it != nullptr; it = it->nexts[0]) {
            std::cout << it->val << "\t";
            for (int i = 1; i <= it->level; ++i) {
                std::cout << "->" << i;
            }
            std::cout << std::endl;
            ++count;
        }
        std::cout << "================================ size: " << count
                  << " level: " << max_level_ << std::endl;
    }

    int Size() const {
        int count = 0;
        for (Node *it = head_->nexts[0]; it != nullptr; it = it->nexts[0]) {
            ++count;
        }
        return count;
    }

private:
    int RandomLevel() const {
        int level = 1;
        int random = rand();
        while (random & 1) {
            ++level;
            random >>= 1;
        }
        return level;
    }

private:
    int max_level_;
    Node *head_;
};

}  // namespace zfish

#endif  // SKIPLIST_H