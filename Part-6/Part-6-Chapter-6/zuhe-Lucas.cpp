#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, m, p;

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

LL ksm(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

LL C(LL n, LL m) {
    if (m > n) return 0;
    LL a = 1, b = 1;
    for (LL i = n - m + 1; i <= n; ++i) a = a * i % p;
    for (LL i = 2; i <= m; ++i) b = b * i % p;
    return a * ksm(b, p - 2) % p;
}

LL Lucas(LL n, LL m) {
    if (m == 0) return 1;
    return (C(n % p, m % p) * Lucas(n / p, m / p)) % p;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> p;
        cout << Lucas(n, m) << endl;
    }
    
    return 0;
}

