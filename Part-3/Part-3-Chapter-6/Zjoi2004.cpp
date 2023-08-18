#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 10, M = 10000;

struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int n;
int st, ed;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], dfstime, scc[N], bt;
int cut[N];

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v] && u != st && dfn[ed] >= dfn[v]) {
                cut[u] = 1;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    scanf("%d", &n);
    int u, v;
    while (scanf("%d%d", &u, &v) && u != 0 && v != 0) {
        add_edge(u, v);
        add_edge(v, u);
    }
    scanf("%d%d", &st, &ed);
    Tarjan(st);
    
    for (int i = 1; i <= n; i++) {
        if (cut[i] == 1 && i != ed) {
            printf("%d\n", i);
            return 0;
        } 
    }
    
    printf("No solution\n");

    return 0;
}