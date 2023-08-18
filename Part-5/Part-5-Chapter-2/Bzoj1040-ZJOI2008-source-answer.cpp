#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
const ll inf = 0x3f3f3f3f;

int root, fa[N], vis[N];
int n, val[N];
int tot, fir[N];
int nex[N], to[N];
void add(int x, int y) {
    ++tot;
    nex[tot] = fir[x];
    to[tot] = y;
    fir[x] = tot;
}
void dfs(int u) {
    if (vis[u])
        root = u;
    else {
        vis[u] = 1;
        dfs(fa[u]);
    }
}
ll dp[N][2];
void DP(int fa, int u) {
    vis[u] = 1;
    dp[u][0] = 0, dp[u][1] = val[u];

    for (int i = fir[u]; i; i = nex[i]) {
        int v = to[i];

        if (v == fa)
            continue;

        if (v != root) {
            DP(u, v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        } else {
            dp[u][1] = -inf;
        }
    }

    //printf("### %d %d %d\n",u,dp[u][0],dp[u][1]);
}



int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        int t;
        scanf("%d%d", &val[i], &t);
        add(t, i);
        fa[i] = t;
    }

    ll ans = 0;

    for (int i = 1; i <= n; ++i) {
        if (vis[i])
            continue;

        root = -1;
        dfs(i);

        //printf("+++++++ %d\n",root);
        if (root == -1)
            continue;

        DP(-1, root);
        ll t = max(dp[root][0], dp[root][1]);
        root = fa[root];
        DP(-1, root);
        ans += max(t, max(dp[root][0], dp[root][1]));
    }

    printf("%lld\n", ans);
    return 0;
}