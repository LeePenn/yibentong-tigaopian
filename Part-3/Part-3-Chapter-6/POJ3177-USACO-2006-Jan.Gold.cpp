#include <bits/stdc++.h>
using namespace std;

const int N = 5000 + 10, M = 10000 + 10;
int n, m;
struct Edge {
    int nxt, v, op;
    Edge() { nxt = v = op = 0; }
    Edge(int _nxt, int _v, int _op) {
        nxt = _nxt;
        v = _v;
        op = _op;
    }
}edge[M << 1];
int hd[N], etot;

void add_edge(int u, int v) {
    etot++;
    edge[etot] = Edge(hd[u], v, etot + 1);
    hd[u] = etot;
    etot++;
    edge[etot] = Edge(hd[v], u, etot - 1);
    hd[v] = etot;
}

int dfn[N], low[N], dfstime, st[N], top, cnt, scc[N];
bool vis[M << 1];

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        if (!vis[edge[i].op]) {
            vis[i] = true;
            int v = edge[i].v;
            if (!dfn[v]) {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        } 
        vis[i] = true;
    }
    if (dfn[u] == low[u]) {
        cnt++;
        int cur;
        do {    
            cur = st[top--];
            scc[cur] = cnt;
        } while (cur != u);
    }
}

int ind[N];

void Statis() {
    for (int u = 1; u <= n; u++) {
        for (int i = hd[u]; i; i = edge[i].nxt) {
            if (vis[edge[i].op]) {
                int v = edge[i].v;
                if (scc[u] != scc[v]) {
                    ind[scc[u]]++;
                    ind[scc[v]]++;
                }
            }
            vis[i] = 0;
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (ind[i] == 1) ans++;
    }
    printf("%d\n", (ans + 1) / 2);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    
    Tarjan(1);
    Statis();
    
    return 0;
}