#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100000 + 10;
LL x, y, m, n, L;

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
    if (n < m) {
        swap(m, n), swap(x, y);
    }
    LL a, b, d;
    Exgcd(n - m, L, d, a, b);
    if ((x - y) % d != 0 || m == n) printf("Impossible\n");
    else {
        LL k = L / d;
        printf("%lld\n", (a * (x - y) / d % k + k) % k);
    }
}

int main() {
    while (scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &L) == 5) {
        Work();
    }
    

    return 0;
}