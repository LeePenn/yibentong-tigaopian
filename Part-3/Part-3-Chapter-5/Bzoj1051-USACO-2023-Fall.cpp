#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 5e5 + 10;
int n, m; 
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int NXT, int V) {
        nxt = NXT;
        v = V;
    }
}edge[M];
int hd[N], tot;

int dfn[N], low[N], t, st[N], top, co[N], col, sz[N];
int in[N];

void add_edge(int u, int v) {
    edge[++tot] = Edge(hd[u], v);
    hd[u] = tot;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++t;
    st[++top] = u;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!co[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        co[u] = ++col;
        sz[col]++;
        while (st[top] != u) {
            co[st[top]] = col;
            sz[col]++;
            top--;
        }
        top--;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        add_edge(v, u);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    
    
    for (int i = 1; i <= n; i++) {
        for (int j = hd[i]; j; j = edge[j].nxt) {
            if (co[i] != co[edge[j].v]) {
                in[co[edge[j].v]]++;
            }
        }
    }
    
    int ans = 0, u = 0;
    for (int i = 1; i <= col; i++) {
        if (in[i] == 0) {
            ans = sz[i];
            u++;
        }
    }
    
    if (u == 1) printf("%d\n", ans);
    else printf("0\n");

    return 0;
}