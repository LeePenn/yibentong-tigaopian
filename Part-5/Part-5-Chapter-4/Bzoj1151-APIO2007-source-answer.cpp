#include <bits/stdc++.h>
using namespace std;
using LL = long long;
LL num[10006][40], f[10006][40], ans;
int main() {
    LL n, m, x, y, z, t, a, b;
    cin >> n >> m;

    for (LL i = 1; i <= m; ++i) {
        a = b = 0;
        cin >> x >> y >> z;

        for (LL i = 1; i <= y; ++i) {
            cin >> t;
            t = (t - x + n) % n;
            a |= (1 << t);
        }

        for (LL i = 1; i <= z; ++i) {
            cin >> t;
            t = (t - x + n) % n;
            b |= (1 << t);
        }

        for (LL i = 0; i < 32; ++i) {
            if (a & (~i) || b & i) {
                num[x][i]++;
            }
        }
    }

    for (LL i = 0; i < 32; ++i) {
        memset(f[0], -0x3f, sizeof(f[0]));
        f[0][i] = 0;

        for (LL j = 1; j <= n; ++j) {
            for (LL k = 0; k < 32; ++k) {
                f[j][k] = max(f[j - 1][(k & 15) << 1], f[j - 1][((k & 15) << 1) | 1]) + num[j][k];
            }
        }

        ans = max(f[n][i], ans);
    }

    cout << ans << "\n";
    return 0;
}