#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100000 + 10;
LL n, p[N], v[N];
LL tot;
LL b[N], t[N];

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

void Init() {
    for (LL i = 2; i < 100000; ++i) {
        if (v[i] == 0) {
            v[i] = i;
            p[++tot] = i;
        }
        
        for (LL j = 1; j <= tot; ++j) {
            if (p[j] > v[i] || p[j] * i > 100000) break;
            v[p[j] * i] = p[j];
        }
    }
}

void Work() {
    memset(t, 0, sizeof(t));
    LL s = 0, cnt = 0;
    for (int j = 1; j <= tot; ++j) {
        if (n % p[j] == 0) {
            b[++cnt] = p[j];
            while (n % p[j] == 0) {
                t[p[j]]++;
                n /= p[j];
            }
            s += t[p[j]];
            
        }
        if (p[j] > n) break;
    }
    
    if (n > 1) s++;
    
    printf("%lld ", s);
    
    LL ans = 1;
    for (int i = 1; i <= s; ++i) {
        ans *= i;
    }
    
    for (int i = 1; i <= cnt; ++i) {
        LL c = 1;
        for (int j = 1; j <= t[b[i]]; ++j) {
            c *= j;
        }
        ans /= c;
    }
    printf("%lld\n", ans);
}

int main() {
    Init();
    
    while (scanf("%lld", &n) == 1) {
        Work();
    }
    
    return 0;
}