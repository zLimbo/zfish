#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// 四则运算辅助函数
int helper(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}

// 读取从i开始的整数，引用j表示该整数的最后一位的位置
int get_int(int i, int& j, string& s) {
    while (isdigit(s[j + 1]))
        j++;
    return atoi(s.substr(i, j - i + 1).c_str());
}

// 运算一个不带括号的式子
int cal(string s) {
    stack<int> nums;
    stack<int> ops;
    int len = s.length();
    if (s[0] == '-')
        nums.push(0);
    for (int i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            // 数字直接入栈
            int j = i;
            nums.push(get_int(i, j, s));
            i = j;
        } else {
            // 读到运算符进行运算
            // 乘/除法运算直接拿下一个数字进行运算
            if (s[i] == '*' || s[i] == '/') {
                int j = i + 1;
                int next_num = get_int(i + 1, j, s);
                int num = nums.top();
                nums.pop();
                nums.push(helper(num, next_num, s[i]));
                i = j;
            } else {
                // 加/减法运算，如果运算符栈不为空(一定是加/减)，则进行前面式子的运算
                if (!ops.empty()) {
                    int right = nums.top();
                    nums.pop();
                    int left = nums.top();
                    nums.pop();
                    nums.push(helper(left, right, ops.top()));
                    ops.pop();
                }
                ops.push(s[i]);
            }
            // 运算符后有减号，说明下一个数是负数，提前读取入栈
            if (s[i + 1] == '-') {
                int j = i + 2;
                int neg = get_int(i + 2, j, s) * (-1);
                nums.push(neg);
                i = j;
            }
        }
    }
    // 因为加/减法是算前面的加减法，最后可能有剩余一个加法运算
    if (!ops.empty()) {
        int right = nums.top();
        nums.pop();
        int left = nums.top();
        nums.pop();
        nums.push(helper(left, right, ops.top()));
        ops.pop();
    }
    return nums.top();
}

int main() {
    vector<string> v = {"10+2*3", "(10+2)*3", "-(10+2)*3", "((1+2)*(-20+1))", "2+3-(5+2)"};

    for (auto& s : v) {
        // 去括号
        if (s.find('(') != s.npos) {
            stack<int> kuohao;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '(') {
                    kuohao.push(i);
                } else if (s[i] == ')') {
                    int left = kuohao.top();
                    string tmp = s.substr(left + 1, i - left - 1);
                    s = s.substr(0, left) + std::to_string(cal(tmp)) + s.substr(i + 1);
                    i = left - 1;
                    kuohao.pop();
                }
            }
            cout << cal(s) << endl;
        } else {
            cout << cal(s) << endl;
        }
    }
}
