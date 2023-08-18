#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 1e6 + 10, LOGN = 23;

int n, m;
struct Edge {
    int nxt, v, type;
    Edge() { nxt = v = type = 0; }
    Edge(int _nxt, int _v, int _type) {
        nxt = _nxt;
        v = _v;
        type = _type;
    }
}edge[M];
int hd[N], etot;
int dep[N], f[N][LOGN];
int w[N];

void add_edge(int u, int v, int type) {
    edge[++etot] = Edge(hd[u], v, type);
    hd[u] = etot;
}

void initLCA(int u, int pa) {
    dep[u] = dep[pa] + 1;
    for (int i = 0; i <= 20; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (pa == v) continue;
        f[v][0] = u;
        initLCA(v, u);
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    
    for (int i = 20; ~i; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            x = f[x][i];
        }
        if (x == y) return x;
    }
    for (int i = 20; ~i; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

void initRead() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, 0); add_edge(v, u, 0);
    }
    initLCA(1, 0);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        w[u]++; w[v]++;
        w[LCA(u, v)] -= 2;
    }
}

void dfs(int u, int pa) {
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        dfs(v, u);
        w[u] += w[v];
    }
}

int main() {
    initRead();
    dfs(1, 0);
    
    LL ans = 0;
    for (int i = 2; i <= n; i++) {
        if (w[i] == 0) {
            ans += m;
        } else if (w[i] == 1) {
            ans++;
        }
    }
    
    printf("%lld\n", ans);

    return 0;
}