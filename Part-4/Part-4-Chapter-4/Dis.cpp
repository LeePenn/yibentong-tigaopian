#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10, LOGN = 22;
int n, m;
struct Edge {
    int nxt, v, w;
    Edge() { nxt = v = w = 0; }
    Edge(int _nxt, int _v, int _w) {
        nxt = _nxt;
        v = _v;
        w = _w;
    }
}edge[N << 1];
int hd[N], etot;
int f[N][LOGN], dist[N][LOGN], dep[N];

void add_edge(int u, int v, int w) {
    edge[++etot] = Edge(hd[u], v, w);
    hd[u] = etot;
}

void Read() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w); add_edge(v, u, w);
    }
}

void Dfs(int u, int pa) {
    dep[u] = dep[pa] + 1;
    for (int i = 0; i <= log2(dep[u]) + 1; i++) {
        f[u][i + 1] = f[f[u][i]][i];
        dist[u][i + 1] = dist[f[u][i]][i] + dist[u][i];
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        f[v][0] = u;
        dist[v][0] = edge[i].w;
        Dfs(v, u);
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = log2(dep[u] - dep[v]);
    for (int i = k + 1; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;
    for (int i = log2(dep[u]) + 1; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    
    return f[u][0];
}

int get_dist(int u, int lca) {
    int ans = 0;
    int k = log2(dep[u] - dep[lca]);
    for (int i = k + 1; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[lca]) {
            ans += dist[u][i];
            u = f[u][i];
        }
    }
    return ans;
}

void calc() {
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        int lca = LCA(u, v);
        int d1 = get_dist(u, lca);
        int d2 = get_dist(v, lca);
        printf("%d\n", d1 + d2);
    }
}

int main() {
    Read();
    Dfs(1, 0);
    
    calc();
    
    return 0;
}