#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 110;
const int inf = 0x3f3f3f3f;

int n, val[N];
int dp[N][N], path[N][N];

int dfs(int l, int r) {
    if (l > r)
        return 1;

    if (dp[l][r] != 0)
        return dp[l][r];

    if (l == r) {
        path[l][r] = l;
        return val[l];
    }

    for (int i = l; i <= r; ++i) {
        int t1 = (l <= i - 1) ? dfs(l, i - 1) : 1;
        int t2 = (i + 1 <= r) ? dfs(i + 1, r) : 1;

        if (dp[l][r] < t1 * t2 + val[i]) {
            dp[l][r] = t1 * t2 + val[i];
            path[l][r] = i;
        }
    }

    return dp[l][r];
}
void pt(int l, int r) {

    if (l > r)
        return;

    printf("%d ", path[l][r]);

    if (l == r)
        return;

    pt(l, path[l][r] - 1);
    pt(path[l][r] + 1, r);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &val[i]);
    }

    dfs(1, n);
    printf("%d\n", dp[1][n]);
    pt(1, n);
    return 0;
}