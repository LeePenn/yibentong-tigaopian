#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#define in inline
#define re register
#define int long long
#define itn int
#define FOR(i,a,b) for(re int i=a;i<=b;i++)
#define ROF(i,a,b) for(re int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int M = 3e5 + 5;
const int INF = 0x3f3f3f3f;
in int read();
int n, m, k;
struct E {
    int nex, to, w;
} edge[M << 1];
struct EE {
    int u, v, w;
} K[M];
int cnt = 0, head[N];
void add(int u, int v, int w) {
    edge[++cnt].nex = head[u];
    edge[cnt].w = w;
    edge[cnt].to = v;
    head[u] = cnt;
}
int dep[N], f[N][30], fm[N][30], sm[N][30], g[N];
bool vis[N];
int W;
bool cmp(EE x, EE y) {
    return x.w < y.w;
}
int get(int k) {
    return g[k] == k ? g[k] : g[k] = get(g[k]);
}
void kruskal() {
    int tot = 0;
    sort(K + 1, K + 1 + m, cmp);
    FOR(i, 1, m) {
        int u = K[i].u, v = K[i].v, w = K[i].w;

        if (u == v) {
            vis[i] = 1;
            continue;
        }

        int fu = get(u);
        int fv = get(v);

        if (fu == fv)
            continue;

        vis[i] = 1;
        g[fu] = fv;
        W += w;
        tot++;
        add(u, v, w);
        add(v, u, w);

        if (tot == n - 1)
            break;
    }
    return ;
}
void dfs(int u, int fa) {
    for (int i = 1; (1 << i) <= dep[u] + 1; i++) {
        f[u][i] = f[f[u][i - 1]][i - 1];
        int ff = f[u][i - 1];
        fm[u][i] = max(fm[u][i - 1], fm[ff][i - 1]);
        sm[u][i] = max(sm[u][i - 1], sm[ff][i - 1]);

        if (fm[u][i - 1] < fm[ff][i - 1])
            sm[u][i] = max(fm[u][i - 1], sm[u][i]);

        if (fm[u][i - 1] > fm[ff][i - 1])
            sm[u][i] = max(fm[ff][i - 1], sm[u][i]);
    }

    for (int i = head[u]; i; i = edge[i].nex) {
        int y = edge[i].to;

        if (y == fa)
            continue;

        dep[y] = dep[u] + 1;
        f[y][0] = u;
        fm[y][0] = edge[i].w;
        dfs(y, u);
    }

    return ;
}
int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    int k = dep[u] - dep[v];

    for (int i = log2(k) + 1; i >= 0; i--)
        if (k >> i & 1)
            u = f[u][i];

    if (u == v)
        return u;

    for (int i = log2(dep[u]) + 1; i >= 0; i--)
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }

    return f[u][0];
}
int findmax(int u, int lca, int val) {
    int ans = 0;

    for (int i = log2(dep[u] - dep[lca]) + 1; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[lca]) {
            if (fm[u][i] == val)
                ans = max(ans, sm[u][i]);
            else
                ans = max(ans, fm[u][i]);

            u = f[u][i];
        }
    }

    return ans;
}
void calc() {
    int ans = 1e18;
    FOR(i, 1, m) {
        if (vis[i])
            continue;

        EE t = K[i];
        int u = K[i].u, v = K[i].v, w = K[i].w;
        int lca = LCA(u, v);
        int a1 = findmax(u, lca, w);
        int a2 = findmax(v, lca, w);

        if (max(a1, a2) != w)
            ans = min(ans, W - max(a1, a2) + w);
    }
    printf("%lld", ans);
    return ;
}
signed main() {
    //  freopen("10133.in","r",stdin);
    //  freopen("10133.out","w",stdout);
    scanf("%lld%lld", &n, &m);
    FOR(i, 1, n) g[i] = i;
    FOR(i, 1, m)
    scanf("%lld%lld%lld", &K[i].u, &K[i].v, &K[i].w);
    kruskal();
    dep[1] = 1;
    dfs(1, 0);
    calc();
    return 0;
}


in int read() {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    return f * x;
}