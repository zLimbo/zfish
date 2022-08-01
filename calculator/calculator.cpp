#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>

using namespace std;

map<pair<char, char>, char> PRIORITY = {
    {{'+', '+'}, '<'}, {{'+', '-'}, '<'}, {{'+', '*'}, '<'}, {{'+', '/'}, '<'}, {{'+', '^'}, '<'},
    {{'+', '!'}, '<'}, {{'+', '('}, '>'}, {{'+', ')'}, '0'}, {{'+', '$'}, '>'}, {{'-', '+'}, '<'},
    {{'-', '-'}, '<'}, {{'-', '*'}, '<'}, {{'-', '/'}, '<'}, {{'-', '^'}, '<'}, {{'-', '!'}, '<'},
    {{'-', '('}, '>'}, {{'-', ')'}, '0'}, {{'-', '$'}, '>'}, {{'*', '+'}, '>'}, {{'*', '-'}, '>'},
    {{'*', '*'}, '<'}, {{'*', '/'}, '<'}, {{'*', '^'}, '<'}, {{'*', '!'}, '<'}, {{'*', '('}, '>'},
    {{'*', ')'}, '0'}, {{'*', '$'}, '>'}, {{'/', '+'}, '>'}, {{'/', '-'}, '>'}, {{'/', '*'}, '<'},
    {{'/', '/'}, '<'}, {{'/', '^'}, '<'}, {{'/', '!'}, '<'}, {{'/', '('}, '>'}, {{'/', ')'}, '0'},
    {{'/', '$'}, '>'}, {{'^', '+'}, '>'}, {{'^', '-'}, '>'}, {{'^', '*'}, '>'}, {{'^', '/'}, '>'},
    {{'^', '^'}, '<'}, {{'^', '!'}, '<'}, {{'^', '('}, '>'}, {{'^', ')'}, '0'}, {{'^', '$'}, '>'},
    {{'!', '+'}, '>'}, {{'!', '-'}, '>'}, {{'!', '*'}, '>'}, {{'!', '/'}, '>'}, {{'!', '^'}, '>'},
    {{'!', '!'}, '<'}, {{'!', '('}, '>'}, {{'!', ')'}, '0'}, {{'!', '$'}, '>'}, {{'(', '+'}, '>'},
    {{'(', '-'}, '>'}, {{'(', '*'}, '>'}, {{'(', '/'}, '>'}, {{'(', '^'}, '>'}, {{'(', '!'}, '>'},
    {{'(', '('}, '>'}, {{'(', ')'}, '0'}, {{'(', '$'}, '>'}, {{')', '+'}, '<'}, {{')', '-'}, '<'},
    {{')', '*'}, '<'}, {{')', '/'}, '<'}, {{')', '^'}, '<'}, {{')', '!'}, '<'}, {{')', '('}, '='},
    {{')', ')'}, '0'}, {{')', '$'}, '>'}, {{'$', '+'}, '<'}, {{'$', '-'}, '<'}, {{'$', '*'}, '<'},
    {{'$', '/'}, '<'}, {{'$', '^'}, '<'}, {{'$', '!'}, '<'}, {{'$', '('}, '0'}, {{'$', ')'}, '0'},
    {{'$', '$'}, '='},
};

char priority(char c1, char c2) {
    return PRIORITY[{c1, c2}];
}

long long quick_pow(long long x, long long n) {
    if (n == 0)
        return 1;
    long long ret = 1;
    while (n) {
        if (n & 1)
            ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

double calculate(const double& num1, const char& sm, const double& num2) {
    switch (sm) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '^':
            return (double)quick_pow(num1, num2);
    }
    return 0.0;
}

double Fac(const double& num) {
    if (num == 1)
        return num;
    else
        return num * Fac(num - 1);
}

double calculate(const string& Formula) {
    stack<double> arithNum;
    stack<char> arithSmb;
    arithSmb.push('$');
    bool link = false;
    for (size_t cnt = 0; !arithSmb.empty(); ++cnt) {
        char ch = Formula[cnt];
        if (isdigit(ch)) {
            if (link) {
                double tempN = arithNum.top();
                arithNum.pop();
                arithNum.push(tempN * 10 + ch - '0');
            } else
                arithNum.push(ch - '0');
            link = true;
        } else {
            char priSm = priority(ch, arithSmb.top());
            if (priSm == '>')
                arithSmb.push(ch);
            else if (priSm == '=')
                arithSmb.pop();
            else {
                char smb = arithSmb.top();
                arithSmb.pop();
                double num1 = arithNum.top();
                arithNum.pop();
                if (smb == '!')
                    arithNum.push(Fac(num1));
                else {
                    double num2 = arithNum.top();
                    arithNum.pop();
                    arithNum.push(calculate(num2, smb, num1));
                    cout << num2 << smb << num1 << "=" << calculate(num2, smb, num1) << endl;
                }
                --cnt;
            }
            link = false;
        }
    }
    return arithNum.top();
}

int main() {
    string s;
    cin >> s;
    cout << calculate(s) << endl;
    return 0;
}
