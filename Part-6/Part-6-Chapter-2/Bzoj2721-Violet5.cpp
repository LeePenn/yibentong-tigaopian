#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10, MOD = 1e9 + 7;
int n, v[N], prime[N], tot;
bool is_p[N];
LL a[N];

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
    for (int i = 2; i < N; ++i) {
        if (!v[i]) {
            v[i] = i;
            prime[++tot] = i;
            is_p[i] = 1;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i >= N) break;
            
            v[prime[j] * i] = prime[j];
        }
    }
}

void Work() {
    n = ReadInt();
    LL ans = 1;
    for (int i = 1; i <= tot; ++i) {
        for (LL j = prime[i]; j <= n; j *= prime[i]) {
            a[i] += n / j;
            a[i] %= MOD;
        }
    }
    
    for (int i = 1; i <= tot; ++i) {
        ans = (ans * (a[i] << 1 | 1)) % MOD;
    }
    
    printf("%lld\n", ans);
}

int main() {
    Init();
    
    Work();

    return 0;
}