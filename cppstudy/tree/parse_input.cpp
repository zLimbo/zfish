
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x, TreeNode *l = nullptr, TreeNode *r = nullptr)
        : val(x), left(l), right(r) {}
};

vector<string> split(const string &sv, const string &delims) {
    vector<string> words;
    auto b = sv.find_first_not_of(delims);
    auto e = sv.find_first_of(delims, b);

    while (b != string::npos) {
        e = min(e, sv.size());
        words.push_back(sv.substr(b, e - b));
        b = sv.find_first_not_of(delims, e);
        e = sv.find_first_of(delims, b);
    }
    return words;
}

string join(const vector<string> &words, const string &delims) {
    if (words.empty()) return "";
    string res{words[0]};
    for (size_t i = 1; i < words.size(); ++i) {
        res += delims + words[i];
    }
    return res;
}

TreeNode *build(vector<string> &words) {
    if (words.empty() || words[0] == "null") return nullptr;
    TreeNode *root = new TreeNode(stoi(words[0].c_str()));
    queue<TreeNode *> q;
    q.push(root);
    int k = 1;
    while (!q.empty()) {
        TreeNode *tp = q.front();
        q.pop();
        if (k >= words.size()) break;
        if (string &w = words[k++]; w != "null") {
            tp->left = new TreeNode(stoi(w));
            q.push(tp->left);
        }
        if (k >= words.size()) break;
        if (string &w = words[k++]; w != "null") {
            tp->right = new TreeNode(stoi(w));
            q.push(tp->right);
        }
    }
    return root;
}

vector<string> print(TreeNode *root) {
    if (!root) return {};
    vector<string> words;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *tp = q.front();
        q.pop();
        if (!tp) {
            words.push_back("null");
            continue;
        }
        words.push_back(to_string(tp->val));
        q.push(tp->left);
        q.push(tp->right);
    }
    while (!words.empty() && words.back() == "null") words.pop_back();
    return words;
}

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        if (!root) return "";
        string data;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *tp = q.front();
            q.pop();
            if (!tp) {
                data.push_back((unsigned char)255);
                continue;
            }
            int x = tp->val;
            if (x < 128) {
                data.push_back(x);
            } else {
                data.push_back((unsigned char)(128 | (x % 127)));
                data.push_back((unsigned char)(x / 127));
            }

            q.push(tp->left);
            q.push(tp->right);
        }
        while (!data.empty() && (unsigned char)data.back() == 255) {
            data.pop_back();
        }
        return data;
    }

    TreeNode *one(string &data, int &k) {
        if (k >= data.size()) return nullptr;
        int x = (unsigned char)data[k++];
        if (x == 255) return nullptr;
        if (x >= 128) {
            x = (unsigned char)data[k++] * 127 + (x ^ 128);
        }
        return new TreeNode(x);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        if (data.empty()) return nullptr;
        int k = 0;
        TreeNode *root = one(data, k);
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *tp = q.front();
            q.pop();
            tp->left = one(data, k);
            tp->right = one(data, k);
            if (tp->left) q.push(tp->left);
            if (tp->right) q.push(tp->right);
        }
        return root;
    }
};

int main() {
    string s;
    ifstream fin("in.dat");

    fin >> s;
    auto words = split(s, "[], ");

    // for (auto &w : words) {
    //     cout << w << " ";
    // }
    // cout << endl;

    cout << "split ok" << endl;
    auto root = build(words);
    cout << "build ok" << endl;

    string data = Codec().serialize(root);
    root = Codec().deserialize(data);

    auto ps = print(root);
    cout << "print ok" << endl;
    string res = "[" + join(ps, ",") + "]";

    printf("words.len=%ld, ps.len=%ld\n", words.size(), ps.size());

    ofstream fout("out.dat");
    fout << res;

    return 0;
}