#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL p[N], v[N], tot;
bool is_p[N];
LL n, m;
LL ans[N];

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
    v[1] = 1;
    
    for (int i = 2; i < 100000; ++i) {
        if (!v[i]) {
            v[i] = i;
            p[++tot] = i;
            is_p[i] = 1;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (p[j] > v[i] || p[j] * i > 100000) break;
            
            v[p[j] * i] = p[j];
        }
    }
}

bool is_prime(LL k) {
    if (k < 100000) return is_p[k];
    
    for (int i = 1; p[i] * p[i] <= k; ++i) {
        if (k % p[i] == 0) return 0;
    }
    
    return 1;
}

void Dfs(int pi, LL num, LL cur) {
    if (num == 1) {
        ans[++m] = cur;
        return;
    }
    
    if (num > p[pi] && is_prime(num - 1)) {
        ans[++m] = cur * (num - 1);
    }
    
    for (int i = pi; p[i] * p[i] <= num; ++i) {
        int factor = p[i] + 1, t = p[i];
        
        for (; factor <= num; t *= p[i], factor += t) {
            if (num % factor == 0) {
                Dfs(i + 1, num / factor, cur * t);
            }
        }
    }
}

int main() {
    Init();
    while (scanf("%lld", &n) == 1) {
        m = 0;
        memset(ans, 0, sizeof(ans));
        Dfs(1, n, 1);
        
        printf("%lld\n", m);
        sort(ans + 1, ans + m + 1);
        for (int i = 1; i <= m; ++i) {
            printf("%lld ", ans[i]);
        }
        
        if (m) printf("\n");
    }
    
    return 0;
}