#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL A, B, C, k;

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

void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0, d = a;
        return;
    }
    
    Exgcd(b, a % b, d, x, y);
    LL t = x;
    x = y, y = t - a / b * y;
}

int main() {
    LL a, m, c, d, x, y;
    while (cin >> A >> B >> C >> k && (A || B || C || k)) {
        a = C;
        m = 1LL << k;
        c = B - A;
        Exgcd(a, m, d, x, y);
        if (c % d == 0) {
            x = x * c / d;
            x = ((x % (m / d)) + (m / d)) % (m / d);
            printf("%lld\n", x);
        } else {
            printf("FOREVER\n");
        }
    }
    
    return 0;
}