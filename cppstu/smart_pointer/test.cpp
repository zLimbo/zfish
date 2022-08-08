#include <iostream>
#include <vector>
using namespace std;

int main() {
    freopen("2in.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<int> ps1(n + 1), ps2(n + 1);
    for (int i = 0; i < n; ++i) {
        ps1[i + 1] = ps1[i];
        ps2[i + 1] = ps2[i];
        if (v[i] <= 0) {
            ps1[i + 1] = ps1[i] + 1;
        }
        if (v[i] >= 0) {
            ps2[i + 1] = ps2[i] + 1;
        }
        
    }

    int res = ps2[n];
    for (int i = 0; i < n; ++i) {
        int k = ps2[i] + ps1[n] - ps1[i];
        res = min(res, k);
        
    }
    cout << res << endl;
    return 0;
}

// #include <iostream>

// using namespace std;

// int main() {
//     // freopen("in.txt", "r", stdin);

//     int n;
//     cin >> n;

//     while (n--) {
//         int x, y;
//         cin >> x >> y;

//         if (x > y)
//             swap(x, y);

//         if (x * 2 <= y) {
//             cout << x << endl;
//             continue;
//         }

//         int res = min(x, y / 2);
//         x -= res;
//         y -= res * 2;

//         int k = x / 2;
//         while (k >= 1) {
//             int b = (k - y) + 1 / 2;
//             res -= b;
//             res += k;
//             k = b;
//             // cout << x << " " << y << " " << k << " " << b << endl;
//             y = y + b * 2 - k;
//         }

//         cout << res << endl;

//         // if (x * 2 <= y) {
//         //   cout << x << endl;
//         // } else {
//         //   int res = min(x, y / 2);
//         //   x -= y / 2;
//         //   y -=
//         //   if (x >= 2 && (y & 1)) {
//         //     ++res;
//         //   }
//         //   cout << res << endl;
//         // }
//     }

//     return 0;
// }