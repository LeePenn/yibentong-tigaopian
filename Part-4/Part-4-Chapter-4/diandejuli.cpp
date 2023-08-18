#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOGN = 22;

int n, m;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[N << 1];
int hd[N], etot;
int f[N][LOGN], dep[N];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void initRead() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
}

void initLCA(int u, int pa) {
    dep[u] = dep[pa] + 1;
    for (int i = 0; i < 20; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    }
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        f[v][0] = u;
        initLCA(v, u);
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
        if (x == y) return x;
    }
    
    for (int i = 20; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    
    return f[x][0];
}

int dist(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[LCA(x, y)];
}

int main() {
    initRead();
    initLCA(1, 0);
    
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", dist(u, v));
    }

    return 0;
}