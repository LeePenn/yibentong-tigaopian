#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, k, b[N], c[N], v[N], w[N], dp[N], cnt = 0, minn = 9999999;
int main() {
    cin >> n;
    memset(dp, 9999999, sizeof(dp));

    for (int i = 1; i <= n; i++)
        cin >> b[i];

    for (int i = 1; i <= n; i++)
        cin >> c[i];

    cin >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= c[i]; j *= 2) {
            cnt++;
            v[cnt] = b[i] * j;
            w[cnt] = j;
            c[i] -= j;
        }

        if (c[i])
            cnt++, v[cnt] = b[i] * c[i], w[cnt] = c[i];
    }

    dp[0] = 0;

    for (int i = 1; i <= cnt; i++)
        for (int j = k; j >= v[i]; j--)
            dp[j] = min(dp[j], dp[j - v[i]] + w[i]);

    cout << dp[k];
    return 0;
}