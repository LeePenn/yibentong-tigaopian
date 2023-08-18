#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 10, M = 1e6 + 10;
int n;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int x[M], y[M], m;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], tim, st[N], top, co[N], col;

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
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
        while (st[top] != u) {
            co[st[top]] = col;
            top--;
        }
        top--;
    }
}

int ind[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int tmp;
            scanf("%d", &tmp);
            if (tmp == 1) {
                add_edge(i, j);
                x[etot] = i;
                y[etot] = j;
            }
        }
    }
    
    m = etot;
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    
    for (int i = 1; i <= m; i++) {
        x[i] = co[x[i]];
        y[i] = co[y[i]];
        if (x[i] != y[i]) {
            ind[y[i]]++;
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= col; i++) {
        if (ind[i] == 0) ans++;
    }
    printf("%d\n", ans);
}