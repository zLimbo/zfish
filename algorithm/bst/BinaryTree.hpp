
#ifndef __BINARY_TREE__HPP__
#define __BINARY_TREE__HPP__


#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

namespace zLimbo {

template <typename T>
struct TreeNode {
    T val;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    unsigned height = 0;
    unsigned depth = 0;

    explicit TreeNode(
            T val,
            TreeNode* parent = nullptr,
            TreeNode* left = nullptr,
            TreeNode* right = nullptr):
        val(val), parent(parent), left(left), right(right) {}
};




template <typename T>
class BinaryTree {

protected:
    unsigned int _size = 0;
    TreeNode<T>* root = nullptr;

protected:
    bool isLeft(TreeNode<T>* tn) const { return tn == root ? false : tn == tn->parent->left; }
    bool isRight(TreeNode<T>* tn) const { return tn == root ? false : tn == tn->parent->right; }
    bool isLeaf(TreeNode<T>* tn) const { return !(tn->left) && !(tn->right); }

protected:
    void removeTree(TreeNode<T>* tn);
    void showTree(TreeNode<T>* tn, string prefix = "", bool isLeft = true) const;

public:
    unsigned size() const { return _size; };

public:
    std::vector<T> inorder() const;
    std::vector<T> preorder() const;
    std::vector<T> postorder() const;
    std::vector<T> level() const;
    void showTree() const;

public:
    virtual ~BinaryTree();
    virtual bool search(const T& val) const = 0;
    virtual bool insert(const T& val) = 0;
    virtual bool remove(const T& val) = 0;
};


template <typename T>
void BinaryTree<T>::removeTree(TreeNode<T>* tn) {
    if (!tn) return;
    removeTree(tn->left);
    removeTree(tn->right);
    delete tn;
}


template <typename T>
BinaryTree<T>::~BinaryTree() {
    removeTree(root);
    root = nullptr;
    cout << "free" << endl;
}


template <typename T>
std::vector<T> BinaryTree<T>::inorder() const {
    std::vector<T> data;
    std::stack<TreeNode<T>*> s;
    TreeNode<T>* tn = root;
    while (tn) {
        s.push(tn);
        tn = tn->left;
    }
    while (!s.empty()) {
        tn = s.top(); s.pop();
        //cout << tn->val << " " << (tn == root ? -1: tn->parent->val) << endl;
        data.push_back(tn->val);
        tn = tn->right;
        while (tn) {
            s.push(tn);
            tn = tn->left;
        }
    }
    return data;
}


template <typename T>
std::vector<T> BinaryTree<T>::preorder() const {
    std::vector<T> data;
    std::stack<TreeNode<T>*> s;
    if (root) {
        s.push(root);
    }
    while (!s.empty()) {
        TreeNode<T>* tn = s.top(); s.pop();
        data.push_back(tn->val);
        if (tn->right) {
            s.push(tn->right);
        }
        if (tn->left) {
            s.push(tn->left);
        }
    }
    return data;
}


template <typename T>
std::vector<T> BinaryTree<T>::level() const {
    std::vector<T> data;
    std::queue<TreeNode<T>*> q;
    if (root) {
        q.push(root);
    }
    while (!q.empty()) {
        TreeNode<T>* tn = q.front(); q.pop();
        data.push_back(tn->val);
        if (tn->left) {
            q.push(tn->left);
        }
        if (tn->right) {
            q.push(tn->right);
        }
    }
    return data;
}

template <typename T>
void BinaryTree<T>::showTree() const {
    showTree(root);
}


template <typename T>
void BinaryTree<T>::showTree(TreeNode<T>* tn, string prefix, bool isLeft) const {
    if (tn == nullptr) {
        cout << "Empty tree" << endl;
        return;
    }
    if (tn->right) {
        showTree(tn->right, prefix + (isLeft ? "│   " : "    "), false);
    }
    cout << prefix + (isLeft ? "└── " : "┌── ") + to_string(tn->val) + "\n";
    if (tn->left) {
        showTree(tn->left, prefix + (isLeft ? "│    " : "   "), true);
    }


}

} // namespace zLimbo


#endif
