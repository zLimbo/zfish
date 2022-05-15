#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <assert.h>
#include "zf/debug.h"
using namespace zl;
using namespace std;

struct TreeNode {
    int val;
    int height;
    TreeNode *left, *right;
    TreeNode(int val_, int height_ = 0, TreeNode* left_ = nullptr,
             TreeNode* right_ = nullptr)
        : val(val_), height(height_), left(left_), right(right_) {}
};

class AVLTree {
private:
    TreeNode* root = nullptr;

    int height(TreeNode* tn) {
        if (!tn) return 0;
        return tn->height;
    }

    void updateHeight(TreeNode* tn) {
        tn->height = 1 + max(height(tn->left), height(tn->right));
    }

    TreeNode* minValue(TreeNode* tn) {
        while (tn->left) tn = tn->left;
        return tn;
    }

    int getBalance(TreeNode* tn) {
        return height(tn->left) - height(tn->right);
    }

    TreeNode* leftRotate(TreeNode* parent) {
        TreeNode* child = parent->right;
        parent->right = child->left;
        child->left = parent;
        updateHeight(parent);
        updateHeight(child);
        return child;
    }

    TreeNode* rightRotate(TreeNode* parent) {
        TreeNode* child = parent->left;
        parent->left = child->right;
        child->right = parent;
        updateHeight(parent);
        updateHeight(child);
        return child;
    }

    TreeNode* regainBalance(TreeNode* tn) {
        int balance = getBalance(tn);
        if (balance > 1) {
            int lcBalance = getBalance(tn->left);
            if (lcBalance < 0) tn->left = leftRotate(tn->left);
            tn = rightRotate(tn);
        } else if (balance < -1) {
            int rcBalance = getBalance(tn->right);
            if (rcBalance > 0) tn->right = rightRotate(tn->right);
            tn = leftRotate(tn);
        }
        return tn;
    }

    TreeNode* insert(TreeNode* tn, int val) {
        if (!tn) return new TreeNode(val, 1);
        if (val < tn->val)
            tn->left = insert(tn->left, val);
        else if (val > tn->val)
            tn->right = insert(tn->right, val);

        updateHeight(tn);
        tn = regainBalance(tn);

        return tn;
    }

    TreeNode* remove(TreeNode* tn, int val) {
        if (!tn) return nullptr;
        if (val < tn->val)
            tn->left = remove(tn->left, val);
        else if (val > tn->val)
            tn->right = remove(tn->right, val);
        else {
            if (tn->left == nullptr || tn->right == nullptr) {
                TreeNode* child = tn->left ? tn->left : tn->right;
                delete tn;
                tn = child;
            } else {
                TreeNode* succ = minValue(tn->right);
                tn->val = succ->val;
                tn->right = remove(tn->right, succ->val);
            }
        }

        if (!tn) return nullptr;

        updateHeight(tn);
        tn = regainBalance(tn);

        return tn;
    }

public:
    int height() { return height(root); }

    void insert(int val) { root = insert(root, val); }

    void remove(int val) { root = remove(root, val); }

    void show(TreeNode* tn, string prefix = "", bool isLeft = true) {
        if (tn->right) {
            show(tn->right, prefix + (isLeft ? "┃    " : "     "), false);
        }
        cout << prefix + (isLeft ? "┗━━━ " : "┏━━━ ") << tn->val << "["
             << height(tn) << "]" << endl;
        if (tn->left) {
            show(tn->left, prefix + (isLeft ? "     " : "┃    "), true);
        }
    }

    void show() { show(root); }
};

int main() {
    AVLTree avl;

    for (int i = 0; i < 10; ++i) {
        int val = rand() % 1000;
        cout << val << " ";
        avl.insert(val);
    }
    cout << endl;
    print(RED, "height: ", avl.height());

    cout << "\n" << endl;
    avl.show();
    cout << "\n" << endl;

    string op, num;
    cout << ">>> ";
    while (cin >> op >> num) {
        if (op == "+") {
            avl.insert(stoi(num));
        } else if (op == "-") {
            avl.remove(stoi(num));
        } else {
            break;
        }

        cout << "\n" << endl;
        avl.show();
        cout << "\n" << endl;
        cout << ">>> ";
    }

    return 0;
}
