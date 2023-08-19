#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a[5], m[5], D, T;

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

void Calc() {
    LL d, x, y;
    LL M = m[1] * m[2] * m[3];
    LL ans = 0;
    for (int i = 1; i <= 3; ++i) {
        LL Mi = M / m[i];
        Exgcd(Mi, m[i], d, x, y);
        ans = ((ans + x * Mi * a[i]) % M) + M % M;
        while (ans <= D) ans += M;
    }
    printf("Case %lld: the next triple peak occurs in %lld days.\n", T, ans - D);
}

int main() {
    m[1] = 23, m[2] = 28, m[3] = 33;
    while (scanf("%lld%lld%lld%lld", &a[1], &a[2], &a[3], &D) == 4 && a[1] != -1) {
        T++;
        Calc();
    }
    
    return 0;
}