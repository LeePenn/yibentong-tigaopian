#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 14, MOD = 1e8;

int n, m;
LL f[N][1 << N];
int g[N];
int can[N][1 << N];

void Read() {
    scanf("%d%d", &n, &m);
    int v;
    for (int i = 1; i <= n; ++i) {
        int x = 0;
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &v);
            if (!v) {
                x += (1 << (m - j));
            }
        }
        g[i] = x;
        // printf("%d\n", g[i]);
    }
}

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            if ((j & (j << 1)) || (j & (j >> 1))) continue;
            if (j & g[i]) continue;
            can[i][++can[i][0]] = j;
            // printf("## %d, %d\n", i, j);
        }
    }
}

LL Mod(LL x, int y) {
    return (x % y + y) % y;
}

void DP() {
    for (int i = 1; i <= can[1][0]; ++i) {
        f[1][can[1][i]] = 1;
        // printf("$$$ %d ", can[1][i]);
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= can[i][0]; ++j) {
            f[i][can[i][j]] = 0;
            for (int k = 1; k <= can[i - 1][0]; ++k) {
                if (can[i][j] & can[i - 1][k]) continue;
                
                f[i][can[i][j]] = Mod(f[i][can[i][j]] + f[i - 1][can[i - 1][k]], MOD);
            }
        }
    }
    
    int ans = 0;
    // printf("!! %d\n", can[n][0]);
    for (int i = 1; i <= can[n][0]; ++i) ans = Mod(ans + f[n][can[n][i]], MOD);
    
    printf("%d\n", ans);
}

int main() {
    Read();
    
    init();
    
    DP();

    return 0;
}