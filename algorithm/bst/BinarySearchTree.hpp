#ifndef __BINARY_SEARCH_TREE__HPP__
#define __BINARY_SEARCH_TREE__HPP__


#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include "BinaryTree.hpp"

using std::cout;
using std::endl;

namespace zLimbo {

template <typename T>
class BinarySearchTree: public BinaryTree<T> {

protected:
    std::pair<TreeNode<T>*, int> locate(const T& val) const;
    TreeNode<T>* last(TreeNode<T>* tn) const;
    TreeNode<T>* next(TreeNode<T>* tn) const;

public:
    bool search(const T& val) const override;
    bool insert(const T& val) override;
    bool remove(const T& val) override;
};


template <typename T>
std::pair<TreeNode<T>*, int> BinarySearchTree<T>::locate(const T& val) const {
    TreeNode<T>* tn = this->root;
    if (!tn) return {nullptr, 0};
    while (true) {
        if (val < tn->val) {
            if (!(tn->left)) {
                return {tn, 1};
            }
            tn = tn->left;
        } else if (val > tn->val) {
            if (!(tn->right)) {
                return {tn, 2};
            }
            tn = tn->right;
        } else {
            return {tn, 3};
        }
    }
    return {nullptr, 0};
}


template <typename T>
TreeNode<T>* BinarySearchTree<T>::last(TreeNode<T>* tn) const {
    if (tn->left) {
        tn = tn->left;
        while (tn->right) {
            tn = tn->right;
        }
        return tn;
    }
    if (this->isLeaf(tn)) {
        return nullptr;
    }
    return tn->parent;
}


template <typename T>
TreeNode<T>* BinarySearchTree<T>::next(TreeNode<T>* tn) const {
    if (tn->right) {
        tn = tn->right;
        while (tn->left) {
            tn = tn->left;
        }
        return tn;
    }
    if (isRight(tn)) {
        return nullptr;
    }
    return tn->parent;
}


template <typename T>
bool BinarySearchTree<T>::search(const T& val) const{
    std::cout << locate(val).second << "\t";
    return locate(val).second == 3;
}



template <typename T>
bool BinarySearchTree<T>::insert(const T& val) {
    std::pair<TreeNode<T>*, int> p = locate(val);
    switch (p.second) {
        case 0: this->root = new TreeNode<T>(val); break;
        case 1: p.first->left = new TreeNode<T>(val, p.first); break;
        case 2: p.first->right = new TreeNode<T>(val, p.first); break;
        case 3: return false;
    }
    ++this->_size;
    return true;
}


template <typename T>
bool BinarySearchTree<T>::remove(const T& val) {
    std::pair<TreeNode<T>*, int> p = locate(val);
    if (p.second != 3) {
        return false;
    }
    TreeNode<T>* tn = p.first;
    while (tn->left && tn->right) {
        TreeNode<T>* lastTn = last(tn);
        tn->val = lastTn->val;
        tn = lastTn;
    }
    if (this->isLeaf(tn)) {
        if (tn == this->root) {
            this->root = nullptr;
        } else if (this->isLeaf(tn)) {
            tn->parent->left = nullptr;
        } else {
            tn->parent->right = nullptr;
        }
    } else if (tn->right) {
        if (tn == this->root) {
            this->root = tn->right;
            this->root->parent = nullptr;
        } else {
            tn->right->parent = tn->parent;
            if (this->isLeaf(tn)) {
                tn->parent->left = tn->right;
            } else {
                tn->parent->right = tn->right;
            }
        }
    } else { // tn->left
        if (tn == this->root) {
            this->root = tn->left;
            this->root->parent = nullptr;
        } else {
            tn->left->parent = tn->parent;
            if (this->isLeaf(tn)) {
                tn->parent->left = tn->left;
            } else {
                tn->parent->right = tn->left;
            }
        }
    }
    --this->_size;
    delete tn;
    return true;
}


}// namespace zLimbo


#endif
