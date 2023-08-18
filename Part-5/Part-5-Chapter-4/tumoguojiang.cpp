#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e4 + 10, M = 1010, MOD = 1e6;

int n, m, k;
int f[N][M];
int state[M], cnt;
int st;
int maxc;

void Read() {
    scanf("%d%d%d", &n, &m, &k);
    int x;
    maxc = 1;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x);
        st = st * 3 + (x - 1);
        maxc *= 3;
    }
}

int Mod(int x, int y) {
    return (x % y + y) % y;
}

bool Isnei(int x) {
    int prev = -1, now = -1;
    for (int i = 1; i <= m; ++i) {
        now = x % 3;
        if (now == prev) return 1;
        prev = now;
        x /= 3;
    }
    return 0;
}

void Init() {
    for (int i = 0; i < maxc; ++i) {
        if (Isnei(i)) continue;
        
        state[++cnt] = i;
        if (i == st) f[0][i] = 1;
    }
}

bool Isnei2(int x, int y) {
    for (int i = 1; i <= m; i++) {
        int c1 = x % 3, c2 = y % 3;
        if (c1 == c2) return 1;
        x /= 3, y /= 3;
    }
    return 0;
}

void DP() {
    int l1 = k - 1, l2 = n - k;
    if (l1 > l2) swap(l1, l2);
    
    for (int i = 1; i <= l2; ++i) {
        for (int j1 = 1; j1 <= cnt; ++j1) {
            for (int j2 = 1; j2 <= cnt; ++j2) {
                if (Isnei2(state[j1], state[j2])) continue;
                
                f[i][state[j1]] = Mod(f[i][state[j1]] + f[i - 1][state[j2]], MOD);
            }
        }
    }
    
    LL ans1 = 0, ans2 = 0;
    for (int i = 1; i <= cnt; ++i) {
        ans1 = Mod(ans1 + f[l1][state[i]], MOD);
        ans2 = Mod(ans2 + f[l2][state[i]], MOD);
    }
    
    printf("%lld\n", (ans1 * ans2) % MOD);
}

int main() {
    Read();
    
    if (Isnei(st)) {
        printf("0\n");
        return 0;
    }
    
    Init();
    
    DP();

    return 0;
}