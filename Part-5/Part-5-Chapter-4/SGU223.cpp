#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL f[11][155][155];
LL ans;
int num[155], s[155], n, k, s0;

void init() {
    s0 = 0, ans = 0;
    memset(f, 0, sizeof(f));
    for (int i = 0; i < (1 << n); ++i) {
        if (i & (i << 1)) continue;
        
        int k = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) ++k;
        }
        
        s[++s0] = i;
        num[s0] = k;
    }
}

void DP() {
    f[0][1][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= s0; ++j) {
            for (int kk = num[j]; kk <= k; ++kk) {
                for (int jj = 1; jj <= s0; ++jj) {
                    if (!(s[j] & s[jj]) && !(s[j] & (s[jj] << 1)) && !(s[j] & (s[jj] >> 1))) {
                        f[i][j][kk] += f[i - 1][jj][kk - num[j]];
                    }
                }
            }
        }
    }
    
    for (int i = 1; i <= s0; ++i) ans += f[n][i][k];
    printf("%lld\n", ans);
}

int main() {
    while (cin >> n >> k) {
        init();
        
        DP();
    }


    return 0;
}