#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sort stable_sort
#define endl '\n'
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int d = exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}
int C[16], p[16], l[16];
bool check(int n, int m) {
    int i, j, a, b, c, x, y, d;

    for (i = 1; i < n; i++) {
        for (j = i + 1; j <= n; j++) {
            a = p[i] - p[j];
            b = m;
            c = C[j] - C[i];
            x = y = 0;
            d = exgcd(a, b, x, y);

            if (c % d == 0) {
                x = (x * c / d) % (abs(b / d));
                x = (x + abs(b / d)) % (abs(b / d));

                if (x <= min(l[i], l[j])) {
                    return false;
                }
            }
        }
    }

    return true;
}
int main() {
    int n, i, j, m = 0;
    cin >> n;

    for (i = 1; i <= n; i++) {
        cin >> C[i] >> p[i] >> l[i];
        m = max(m, C[i]);
    }

    while (check(n, m) == false) {
        m++;
    }

    cout << m << endl;
    return 0;
}