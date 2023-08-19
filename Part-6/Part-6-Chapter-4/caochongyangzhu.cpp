#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 15, MOD = 9901;
LL n, a[N], b[N], A[N], Tot = 1;

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
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

void Read() {
    n = ReadLL();
    for (int i = 1; i <= n; ++i) {
        a[i] = ReadLL(), b[i] = ReadLL();
    }
}

void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0, d = a;
        return;
    }
    
    Exgcd(b, a % b, d, x, y);
    LL t = x;
    x = y, y = t - a / b * y;
}

void Work() {
    for (int i = 1; i <= n; ++i) {
        Tot = Tot * a[i];
    }
    for (int i = 1; i <= n; ++i) {
        A[i] = Tot / a[i];
    }
    
    LL d, x, y;
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        Exgcd(A[i], a[i], d, x, y);
        ans = (ans + A[i] * x * b[i] % Tot + Tot) % Tot;
    }
    printf("%lld\n", ans);
}

int main() {
    Read();
    
    Work();
    
    return 0;
}