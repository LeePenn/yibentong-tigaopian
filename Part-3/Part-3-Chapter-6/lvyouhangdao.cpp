#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10, M = 6e4 + 10;

struct Edge {
    int nxt, v, op;
    Edge() { nxt = v = op; }
    Edge(int _nxt, int _v, int _op) {
        nxt = _nxt;
        v = _v;
        op = _op;
    }
}edge[M];
int hd[N], etot;
int n, m;

void add_edge(int u, int v) {
    ++etot;
    edge[etot] = Edge(hd[u], v, etot + 1);
    hd[u] = etot;
    ++etot;
    edge[etot] = Edge(hd[v], u, etot - 1);
    hd[v] = etot;
}

int dfn[N], low[N], dfstime;
bool vis[M];
int cut[M];

void init() {
    etot = dfstime = 0;
    memset(hd, 0, sizeof(hd));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(vis, 0, sizeof(vis));
    memset(cut, 0, sizeof(cut));
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        if (vis[edge[i].op]) continue;
        int v = edge[i].v;
        if (!dfn[v]) {
            vis[i] = true;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) {
                cut[i] = cut[edge[i].op] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) && n && m) {
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
        }
        
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) Tarjan(i);
        }
        
        int ans = 0;
        for (int i = 1; i <= etot; i++) {
            if (cut[i]) ans++;
        }
        printf("%d\n", ans / 2);
    }

    return 0;
}