#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 500 + 3, M = 1e4 + 5;
int n, m, x, y, z;
struct E {
    int u, v;
    int c;
    bool operator < (const E &rh) const {
        return c < rh.c;
    }
}e[M];
int hd[N], nx[M], to[M], w[M], tot;
int fa[N];
int dist[N][N];

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void unionn(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        fa[fu] = fa[fv];
    }
}

void add_edge(int u, int v, int c) {
    nx[++tot] = hd[u];
    to[tot] = v;
    w[tot] = c;
    hd[u] = tot;
}

void dfs(int u, int fa, int d, int di[]) {
    di[u] = d;
    for (int i = hd[u]; i; i = nx[i]) {
        int v = to[i], c = w[i];
        if (v != fa) {
            dfs(v, u, max(d, c), di);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        e[i].u = x, e[i].v = y, e[i].c = z;
    }
    for (int i = 1; i <= n; i++) fa[i] = i;
    
    sort(e + 1, e + m + 1);
    LL ans = 0;
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, c = e[i].c;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            ans += c;
            unionn(fu, fv);
            add_edge(fu, fv, c), add_edge(fv, fu, c);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        dfs(i, -1, 0, dist[i]);
    }
    
    LL ans2 = 1e18;
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, c = e[i].c;
        if (c > dist[u][v]) {
            ans2 = min(ans2, ans + c - dist[u][v]);
        }
    }
    
    printf("%lld\n", ans2);

    return 0;
}