#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100 + 2;

LL n, head[N << 1], tail[N << 1];
LL f[N << 1][N << 1];

void Read() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &head[i]);
        head[n + i] = head[i];
    }
    for (int i = 1; i <= 2 * n - 1; i++) {
        tail[i] = head[i + 1];
    }
    tail[2 * n] = head[1];
    
    for (int i = 1; i <= 2 * n; i++) {
        f[i][i] = 0;
    }
}

void DP() {
    for (int t = 1; t <= n - 1; t++) {
        for (int i = 1; i + t <= 2 * n; i++) {
            int j = i + t;
            f[i][j] = 0;
            for (int k = i; k < j; k++) {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + head[i] * tail[k] * tail[j]);
            }
        }
    }
    
    LL ans = 0;
    for (int i = 1; i <= n; i++) 
        ans = max(ans, f[i][i + n - 1]);
        
    printf("%lld\n", ans);
}

int main() {
    Read();
    DP();

    return 0;
}