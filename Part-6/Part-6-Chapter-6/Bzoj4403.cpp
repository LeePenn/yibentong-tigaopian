#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, L, R, T, P = 1e6 + 3;

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

LL ksm(LL a, LL b, LL p) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

LL inv(LL a, LL p) {
    return ksm(a, p - 2, p) % p;
}

LL C(LL n, LL m) {
    if (m > n) return 0;
    
    LL a = 1, b = 1;
    for (LL i = 1; i <= m; ++i) {
        a = a * (n - m + i) % P;
        b = b * i % P;
    }
    return a * inv(b, P) % P;
}

LL Lucas(LL n, LL m) {
    if (!m) return 1;
    return C(n % P, m % P) * Lucas(n / P, m / P) % P;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> N >> L >> R;
        cout << ((Lucas(R - L + 1 + N, N) - 1) % P + P) % P << endl;
    }
    
    return 0;
}

