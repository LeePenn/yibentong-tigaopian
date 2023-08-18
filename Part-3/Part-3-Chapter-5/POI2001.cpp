#include <bits/stdc++.h>
using namespace std;

const int N = 16000 + 10, M = 1e6 + 10;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int n, m;

inline int pd(int u) {
    return u & 1 ? u + 1 : u - 1;
}

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], tim, st[N], top, col, scc[N];

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st[++top] = u;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!scc[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    
    if (dfn[u] == low[u]) {
        scc[u] = ++col;
        while (st[top] != u) {
            scc[st[top]] = col;
            top--;
        }
        top--;
    }
}

/**
可以这样解决：如果A,B在同一个Party中，而B,C互不相容，则易知如果选了C，则A必选，所以有C --> A，这样可以建立一个有向图。
在这个有向图中，如果存在一条X到Y的路径，则只要X被选中，Y就必选。如果存在一条U到V的路径，而U、V不相容，则U不可选。
可以根据这个性质判断出无解或构造出解。
*/
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, pd(v));
        add_edge(v, pd(u));
    }
    
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    
    for (int i = 1; i <= 2 * n; i += 2) {
        if (scc[i] == scc[i + 1]) {
            printf("NIE\n");
            return 0;
        }
    }
    
    for (int i = 1; i <= n * 2; i += 2) {
        printf("%d\n", scc[i] > scc[i + 1] ? i + 1 : i);
    }
    
    return 0;
}