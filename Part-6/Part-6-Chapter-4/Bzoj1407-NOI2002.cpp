#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20;
LL c[N], p[N], l[N], n, m;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0, d = a;
        return;
    }
    
    exgcd(b, a % b, d, x, y);
    LL t = x;
    x = y, y = t - a / b * y;
}

bool check(LL n, LL m) {
    LL d, x, y;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            LL a = p[i] - p[j];
            LL b = c[j] - c[i];
            LL mod = m;
            d = x = y = 0;
            exgcd(a, mod, d, x, y);
            if (b % d == 0) {
                x = ((x * b / d % abs(mod / d)) + abs(mod / d)) % abs(mod / d);
                if (x <= min(l[i], l[j])) return false;
            }
        }
    }
    
    return true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> p[i] >> l[i];
        m = max(m, c[i]);
    }
    
    while (1) {
        if (check(n, m)) break;
        m++;
    }
    cout << m << endl;
    
    return 0;
}