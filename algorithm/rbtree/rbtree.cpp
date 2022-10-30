#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <assert.h>
#include "debug.h"
using namespace zl;
using namespace std;

struct TreeNode {
    enum COLOR { RED, BLACK };

    int val;
    COLOR color;
    TreeNode *parent, *left, *right;
    TreeNode(int val_, COLOR color_ = RED, TreeNode* parent_ = nullptr,
             TreeNode* left_ = nullptr, TreeNode* right_ = nullptr)
        : val(val_),
          color(color_),
          parent(parent_),
          left(left_),
          right(right_) {}
};

bool haveError = false;
class RBTree {
private:
    TreeNode* root = nullptr;
    TreeNode* hot = nullptr;

    TreeNode* minValue(TreeNode* tn) {
        while (tn->left) tn = tn->left;
        return tn;
    }

    int blackHeight(TreeNode* tn) {
        if (!tn) return 1;
        return blackHeight(tn->left) + (tn->color == TreeNode::BLACK);
    }

    int checkBlackHeight(TreeNode* tn) {
        if (!tn) return 1;
        int lbh = checkBlackHeight(tn->left);
        int rbh = checkBlackHeight(tn->right);
        if (lbh != rbh) {
            cout << "errTn : " << lbh << " " << rbh << endl;
            show(tn);
            show(tn->left);
            show(tn->right);
            assert(0);
        }
        return lbh + (tn->color == TreeNode::BLACK);
    }

    TreeNode* leftRotate(TreeNode* parent) {
        TreeNode* child = parent->right;
        parent->right = child->left;
        child->left = parent;

        if (parent->parent) {
            if (parent == parent->parent->left)
                parent->parent->left = child;
            else
                parent->parent->right = child;
        } else {
            root = child;
            child->parent = nullptr;
        }
        child->parent = parent->parent;
        parent->parent = child;
        if (parent->right) parent->right->parent = parent;

        return child;
    }

    TreeNode* rightRotate(TreeNode* parent) {
        TreeNode* child = parent->left;
        parent->left = child->right;
        child->right = parent;

        if (parent->parent) {
            if (parent == parent->parent->left)
                parent->parent->left = child;
            else
                parent->parent->right = child;
        } else {
            root = child;
            child->parent = nullptr;
        }
        child->parent = parent->parent;
        parent->parent = child;
        if (parent->left) parent->left->parent = parent;

        return child;
    }

    void insertModifyColor(TreeNode* hot) {
#ifdef DEBUG
        cout << "\nInsert: " << hot->val << " "
             << (hot->parent ? hot->parent->val : -1) << endl;
        show();
#endif
        if (hot == root) {
            hot->color = TreeNode::BLACK;
            return;
        }
        TreeNode* parent = hot->parent;
        if (hot->color == TreeNode::RED && parent->color == TreeNode::RED) {
            TreeNode* grandparent = parent->parent;
            TreeNode* uncle = parent == grandparent->left ? grandparent->right
                                                          : grandparent->left;
            if (uncle && uncle->color == TreeNode::RED) {
                parent->color = uncle->color = TreeNode::BLACK;
                grandparent->color = TreeNode::RED;
                insertModifyColor(grandparent);
            } else {
                if (parent == grandparent->left) {
                    if (hot == parent->right) leftRotate(parent);
                    grandparent = rightRotate(grandparent);
                    grandparent->color = TreeNode::BLACK;
                    grandparent->right->color = TreeNode::RED;
                } else {
                    if (hot == parent->left) rightRotate(parent);
                    grandparent = leftRotate(grandparent);
                    grandparent->color = TreeNode::BLACK;
                    grandparent->left->color = TreeNode::RED;
                }
            }
        }
    }

    TreeNode* insert(TreeNode* tn, int val, TreeNode*& hot) {
        if (!tn) return hot = new TreeNode(val, TreeNode::RED);
        if (val < tn->val) {
            tn->left = insert(tn->left, val, hot);
            tn->left->parent = tn;
        } else if (val > tn->val) {
            tn->right = insert(tn->right, val, hot);
            tn->right->parent = tn;
        }
        return tn;
    }

    void removeModifyColor(TreeNode* hot) {
#ifdef DEBUG
        cout << "\nModify: " << hot->val << endl;
        show();
#endif
        if (hot == root) return;
        if (hot->color == TreeNode::RED) {
            hot->color = TreeNode::BLACK;
            return;
        }
        // hot->color == TreeNode::BLACK
        TreeNode* parent = hot->parent;
        if (hot == parent->left) {  // RR, RL
            TreeNode* brother = parent->right;
            if (brother->color == TreeNode::RED) {
                brother->color = parent->color;
                parent->color = TreeNode::RED;
                leftRotate(parent);
                removeModifyColor(hot);  // traceback
            } else {                     // brother->color == TreeNode::BLACK
                TreeNode* lc = brother->left;
                TreeNode* rc = brother->right;
                if (rc && rc->color == TreeNode::RED) {  // RR
                    brother->color = parent->color;
                    parent->color = rc->color = TreeNode::BLACK;
                    leftRotate(parent);
                } else if (lc && lc->color == TreeNode::RED) {  // RL
                    lc->color = parent->color;
                    parent->color = TreeNode::BLACK;
                    rightRotate(brother);
                    leftRotate(parent);
                } else {  // traceback 兄弟节点子节点都为黑色
                    brother->color = TreeNode::RED;
                    removeModifyColor(parent);
                }
            }
        } else {  // hot == parent->right LL, LR
            TreeNode* brother = parent->left;
            if (brother->color == TreeNode::RED) {
                brother->color = parent->color;
                parent->color = TreeNode::RED;
                rightRotate(parent);
                removeModifyColor(hot);
            } else {  // brother->color == TreeNode::BLACK
                TreeNode* lc = brother->left;
                TreeNode* rc = brother->right;
                if (lc && lc->color == TreeNode::RED) {
                    brother->color = parent->color;
                    parent->color = lc->color = TreeNode::BLACK;
                    rightRotate(parent);
                } else if (rc && rc->color == TreeNode::RED) {
                    rc->color = parent->color;
                    parent->color = TreeNode::BLACK;
                    leftRotate(brother);
#ifdef DEBUG
                    cout << "leftRotate: " << endl;
                    show();
#endif
                    rightRotate(parent);
#ifdef DEBUG
                    cout << "rightRotate: " << endl;
                    show();
#endif
                } else {
                    brother->color = TreeNode::RED;
                    removeModifyColor(parent);
                }
            }
        }
    }

    void remove(TreeNode* tn, int val) {
        if (!tn) return;
        if (val < tn->val)
            remove(tn->left, val);
        else if (val > tn->val)
            remove(tn->right, val);
        else {
            if (tn->left && tn->right) {
                TreeNode* succ = minValue(tn->right);
                tn->val = succ->val;
                remove(tn->right, succ->val);
            } else {  // tn->left == nullptr || tn->right == nullptr
                TreeNode* child = tn->left ? tn->left : tn->right;
                if (child && child->color == TreeNode::RED)  // BLACK, RED
                    child->color = TreeNode::BLACK;
                else if (tn->color == TreeNode::BLACK) {  // BLACK, BLACK
                    removeModifyColor(tn);
#ifdef DEBUG
                    cout << "Modify successed" << endl;
                    show();
#endif
                }
                if (tn->parent) {
                    if (child) child->parent = tn->parent;
                    if (tn == tn->parent->left)
                        tn->parent->left = child;
                    else
                        tn->parent->right = child;
                } else {
                    root = child;
                    if (child) child->parent = nullptr;
                }
                delete tn;
            }
        }
    }

    int size(TreeNode* tn) {
        if (!tn) return 0;
        return 1 + size(tn->left) + size(tn->right);
    }

    void show(TreeNode* tn, string prefix = "", bool isLeft = true) {
        if (!tn) return;
        if (tn->right) {
            show(tn->right, prefix + (isLeft ? "┃    " : "     "), false);
        }
        cout << prefix + (isLeft ? "┗━━━ " : "┏━━━ ");
        print(tn->color == TreeNode::RED ? RED : BLACE,
              to_string(tn->val) + "[" +
                  to_string(tn->parent ? tn->parent->val : -1) + "]" + "[" +
                  to_string(blackHeight(tn)) + "]");
        if (tn->left) {
            show(tn->left, prefix + (isLeft ? "     " : "┃    "), true);
        }
    }

public:
    void insert(int val) {
        TreeNode* hot = nullptr;
        root = insert(root, val, hot);
        if (hot) insertModifyColor(hot);
#ifdef DEBUG
        cout << "\nInsert success: " << endl;
        show();
#endif
        checkBlackHeight(root);
    }

    void remove(int val) {
        remove(root, val);
        checkBlackHeight(root);
    }

    int size() { return size(root); }

    void show() {
        cout << size() << endl;
        show(root);
    }
};

// void cmd() {

//     RBTree rbt;

//     cout << ">>> " << endl;
//     string s;
//     while (cin >> s) {
//         if (s == "q") break;
//         int pos = s.find(' ');
//         string op = s.substr(0, pos);
//         // string num = to_string(s);
//         cout << op << " " << num << endl;
//         if (op == "+") {
//             rbt.insert(stoi(num));
//         } else if (op == "-") {
//             rbt.remove(stoi(num));
//         } else {
//             break;
//         }

//         cout << "\n" << endl;
//         rbt.show();
//         cout << "\n" << endl;
//         cout << ">>> ";
//     }
// }

int main() {
    int N = 100;

    RBTree rbt;

    vector<int> v;
    for (int i = 0; i < N; ++i) {
        int val = rand() % 1000;
        v.push_back(val);
        cout << val << " ";
        rbt.insert(val);
    }
    cout << endl;

    cout << "\n" << endl;
    rbt.show();
    cout << "\n" << endl;

    string op, num;
    cout << ">>> ";
    // while (cin >> op >> num) {
    for (int i = 0; i < N; ++i) {
        op = rand() % 2 ? "-" : "+";
        int x = rand() % 1000;
        // for (int x: v) {
        op = "-";
        num = to_string(x);
        cout << op << " " << num << endl;
        if (op == "+") {
            rbt.insert(stoi(num));
        } else if (op == "-") {
            rbt.remove(stoi(num));
        } else {
            break;
        }

        cout << "\n" << endl;
        rbt.show();
        cout << "\n" << endl;
        cout << ">>> ";
    }
    cout << "done !" << endl;

    return 0;
}
