#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 10, M = 1e5 + 10, LOGN = 22;

int n, m;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot, root;
int dep[N], f[N][LOGN];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &u, &v);
        if (v == -1) {
            root = u;
            continue;
        }
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
    scanf("%d", &m);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        int lca = LCA(u, v);
        if (u == lca) printf("1\n");
        else if (v == lca) printf("2\n");
        else printf("0\n");
    }
}

int main() {
    Read();
    Dfs(root, 0);
    calc();

    return 0;
}