#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val, ListNode* next = nullptr) : val(val), next(nullptr) {}
};

int main() {
    int n;
    cin >> n;
    ListNode dummy(0);
    ListNode* cur = &dummy;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cur->next = new ListNode(x);
        cur = cur->next;
    }

    cur = dummy.next;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    ListNode* prev = &dummy;
    cur = prev->next;

    while (cur && cur->next) {
        prev->next = cur->next;
        cur->next = cur->next->next;
        prev->next->next = cur;
        prev = cur;
        cur = cur->next;
    }

    cur = dummy.next;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    return 0;
}