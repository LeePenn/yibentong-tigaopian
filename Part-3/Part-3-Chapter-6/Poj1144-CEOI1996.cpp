#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 10, M = 10000 + 10;

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
int dfn[N], low[N], dfstime, scc[N], bt;
int cut[N];
int root;

void init() {
    etot = 0;
    memset(hd, 0, sizeof(hd));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    memset(cut, 0, sizeof(cut));
    dfstime = 0, bt = 0;
}

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    int cnt = 0;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            cnt++;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if ((u == root && cnt > 1) || (u != root && dfn[u] <= low[v])) {
                cut[u] = 1;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        init();
        int a, b;
        char c;
        while (scanf("%d", &a) == 1 && a) {
            while ((c = getchar()) && c != '\n') {
                scanf("%d", &b);
                add_edge(a, b);
                add_edge(b, a);
            }
        }  
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                root = i;
                Tarjan(i);
            }
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (cut[i]) ans++;
        }
        
        printf("%d\n", ans);
    }

    return 0;
}