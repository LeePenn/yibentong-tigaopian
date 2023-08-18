#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 310;
const ll inf = 1e17;

int n, a[N];
ll dp[N][N];
int path[N][N];
struct node {
    int l, r;
};
int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    for (int d = 2; d <= n; ++d) {

        for (int i = 1; i + d - 1 <= n; ++i) {
            int j = i + d - 1;
            dp[i][j] = -inf;

            for (int k = i; k < j; ++k) {
                //                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+(a[i]+a[j])*a[k]);
                if (dp[i][j] < dp[i][k] + dp[k + 1][j] + (a[i] + a[j])*a[k]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + (a[i] + a[j]) * a[k];
                    path[i][j] = k;
                }
            }
        }
    }

    printf("%lld\n", dp[1][n]);

    queue<node> Q;
    Q.push({1, n});

    while (!Q.empty()) {
        int l = Q.front().l;
        int r = Q.front().r;
        Q.pop();
        printf("%d ", path[l][r]);

        if (l < path[l][r])
            Q.push({l, path[l][r]});

        if (path[l][r] + 1 < r)
            Q.push({path[l][r] + 1, r});
    }

    return 0;
}