#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename K, typename V>
class LruList {
public:
    struct Node {
        K key;
        V val;
        Node* prev;
        Node* succ;
        Node(const K& k, const V& v, Node* prev = nullptr, Node* succ = nullptr)
            : key(k), val(v), prev(prev), succ(succ) {}
    };

    LruList() : dummy(0, 0) {
        dummy.prev = &dummy;
    }

    void update(const K& k, const V& v) {
        auto it = hashmap.find(k);
        if (it != hashmap.end()) {
            Node* node = it->second;
            if (!node->succ) {
                return;
            }
            node->prev->succ = node->succ;
            node->succ->prev = node->prev;
            node->prev = dummy.prev;
            node->prev->succ = node;
            dummy.prev = node;
            node->succ = nullptr;
            node->val = v;
        } else {
            Node* node = new Node(k, v, dummy.prev);
            node->prev->succ = node;
            dummy.prev = node;
            hashmap[k] = node;
        }
    }

    V victim() {
        if (!dummy.succ) {
            throw runtime_error("empty");
        }
        Node* node = dummy.succ;
        dummy.succ = node->succ;
        if (!dummy.succ) {
            dummy.prev = &dummy;
        }
        V v = move(node->val);
        hashmap.erase(node->key);
        delete node;
        return v;
    }

    void show() const {
        for (Node* cur = dummy.succ; cur; cur = cur->succ) {
            cout << "[" << cur->key << "," << cur->val << "] ";
        }
        cout << endl;
    }

    ~LruList() {
        while (dummy.succ) {
            Node* tmp = dummy.succ;
            dummy.succ = tmp->succ;
            delete tmp;
        }
    }

private:
    Node dummy;
    unordered_map<K, Node*> hashmap;
};

int main() {
    LruList<int, int> lru;

    for (int i = 0; i < 10; ++i) {
        lru.update(i, i * 100);
    }

    return 0;
}