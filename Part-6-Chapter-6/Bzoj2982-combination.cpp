#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
LL n, m, T, P = 1e4 + 7;

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
    return ksm(a, p - 2, p);
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
        cin >> n >> m;
        cout << Lucas(n, m) << endl; 
    }
    
    return 0;
}

