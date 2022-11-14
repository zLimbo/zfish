#include <array>
#include <atomic>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;



class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        array<bool, 26> chs;
        for (char ch : allowed)
            chs[ch - 'a'] = true;
        int res = 0;
        for (const string& w : words) {
            bool ok = true;
            for (char ch : w) {
                if (!chs[ch - 'a']) {
                    ok = false;
                    break;
                }
            }
            res += ok;
        }
        return res;
    }
};

class Obj {
    double arr[10];
};

atomic<Obj> atv;
atomic_llong x;

int main() {
    string s = "(1+2)*3*(5+8)*(100/2)";
    cout << "s = " << s << endl;
    stack<char> ops;
    stack<int> nums;
    int p = 0, n = s.size();
    while (p < n) {
        cout << "# p = " << p << endl;
        if (isdigit(s[p])) {
            int x = 0;
            while (p < n && isdigit(s[p])) {
                x = x * 10 + s[p] - '0';
                ++p;
            }
            nums.push(x);
            cout << "# x = " << x << endl;
            if (ops.empty())
                continue;
            if (ops.top() == '*' || ops.top() == '/') {
                int a = nums.top();
                nums.pop();
                int b = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                int c = op == '*' ? a * b : b / a;
                nums.push(c);
            }
        } else {
            cout << "# op = " << s[p] << endl;
            if (s[p] == '(') {
                ops.push(s[p]);
            } else if (s[p] == ')') {
                while (ops.top() != '(') {
                    int a = nums.top();
                    nums.pop();
                    int b = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    int c = op == '+' ? a + b : b - a;
                    nums.push(c);
                }
                ops.pop();
            } else if (s[p] == '+') {
                if (!ops.empty() && ops.top() != '(') {
                    int a = nums.top();
                    nums.pop();
                    int b = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    int c = op == '+' ? a + b : b - a;
                    nums.push(c);
                } else {
                    ops.push(s[p]);
                }
            } else if (s[p] == '-') {
                if (!ops.empty() && ops.top() != '(') {
                    int a = nums.top();
                    nums.pop();
                    int b = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    int c = op == '+' ? a + b : b - a;
                    nums.push(c);
                } else {
                    ops.push(s[p]);
                }
            } else if (s[p] == '*') {
                ops.push(s[p]);
            } else if (s[p] == '/') {
                ops.push(s[p]);
            }
            ++p;
        }
    }

    while (!ops.empty()) {
        int a = nums.top();
        nums.pop();
        int b = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        int c = 0;
        switch (op) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = b - a;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                c = b / a;
                break;
        }
        nums.push(c);
    }
    cout << s << " = " << nums.top() << endl;

    cout << "done" << endl;

    return 0;
}