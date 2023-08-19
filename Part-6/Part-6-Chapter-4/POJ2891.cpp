#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, MOD = 9901;
LL n, a, m, Lcm, now, fail;

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

void Work() {
    scanf("%lld%lld", &m, &a);
    Lcm = m, now = a, fail = 0;
    LL d, x, y, k;
    for (int i = 2; i <= n; ++i) {
        scanf("%lld%lld", &m, &a);
        a = (a - now % m + m) % m;
        Exgcd(Lcm, m, d, x, y);
        if (a % d == 0) {
            k = x * (a / d) % m;
        } else fail = 1;
        
        now += k * Lcm;
        Lcm = Lcm / d * m;
        now = (now % Lcm + Lcm) % Lcm;
    }
    
    if (fail) {
        printf("-1\n");
    } else printf("%lld\n", now);
}

int main() {
    while (scanf("%lld", &n) == 1) {
        Work();
    }
    
    
    
    return 0;
}