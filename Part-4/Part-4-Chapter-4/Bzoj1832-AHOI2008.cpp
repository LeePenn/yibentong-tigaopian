#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, M = 1e6 + 10, LOGN = 22;
int n, m;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int dep[N], f[N][LOGN];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void Dfs(int u, int pa) {
    dep[u] = dep[pa] + 1;
    int k = log2(dep[u]) + 1;
    for (int i = 0; i <= k; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    } 
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        f[v][0] = u;
        Dfs(v, u);
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = log2(dep[u] - dep[v]) + 1;
    for (int i = k; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;
    k = log2(dep[u]) + 1;
    for (int i = k; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

void calc() {
    int x, y, z;
    int pos, ans;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        int x1 = LCA(x, y);
        int x2 = LCA(x, z);
        int x3 = LCA(y, z);
        if (x1 == x2) pos = x3;
        else if (x1 == x3) pos = x2;
        else pos = x1;
        ans = dep[x] + dep[y] + dep[z] - dep[x1] - dep[x2] - dep[x3];
        printf("%d %d\n", pos, ans);
    }
}

int main() {
    Read();
    Dfs(1, 0);
    
    calc();
    
    return 0;
}