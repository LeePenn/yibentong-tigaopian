#include <iostream>
#define INF 1000000000000000000
#define int long long
using namespace std;
int n, maxp, w;
int ap[2010], bp[2010], as[2010], bs[2010];
int f[2010][2010];
int maxn[2010];
int zhan[2010], head, tail;
signed main() {
    cin >> n >> maxp >> w;

    for (int i = 1; i <= n; i++) {
        cin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxp; j++) {
            f[i][j] = -INF;
        }
    }

    f[0][0] = 0;

    for (int j = 1; j <= maxp; j++) {
        maxn[j] = -INF;
    }

    for (int i = 1; i <= n; i++) {
        head = 1;
        tail = 0;

        for (int j = 0; j <= maxp; j++) {
            if (head <= tail && j - zhan[head] > as[i]) {
                head++;
            }

            while (tail >= head && maxn[zhan[tail]] - (j - zhan[tail])*ap[i] < maxn[j]) {
                tail--;
            }

            zhan[++tail] = j;
            f[i][j] = max(f[i][j], maxn[zhan[head]] - (j - zhan[head]) * ap[i]);
        }

        head = 1;
        tail = 0;

        for (int j = maxp; j >= 0; j--) {
            if (head <= tail && zhan[head] - j > bs[i]) {
                head++;
            }

            while (tail >= head && maxn[zhan[tail]] + (zhan[tail] - j)*bp[i] < maxn[j]) {
                tail--;
            }

            zhan[++tail] = j;
            f[i][j] = max(f[i][j], maxn[zhan[head]] + (zhan[head] - j) * bp[i]);
        }

        if (i > w) {
            for (int j = 0; j <= maxp; j++) {
                maxn[j] = max(maxn[j], f[i - w][j]);
            }
        }
    }

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        ans = max(ans, f[i][0]);
    }

    cout << ans;
    return 0;
}