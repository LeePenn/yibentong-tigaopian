#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 10, M = 1e4 + 10;
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

int x[M], y[M];
int ne[M];

bool rule(int u, int v) {
    if (x[u] != x[v]) return x[u] < x[v];
    return y[u] < y[v];
}

void Remove() {
    for (int i = 1; i <= etot; i++) {
        ne[i] = i;
        // printf("$$%d %d %d\n", i, x[i], y[i]);
        x[i] = co[x[i]];
        y[i] = co[y[i]];
        // printf("##%d %d %d\n", i, x[i], y[i]);
    }
    sort(ne + 1, ne + etot + 1, rule);
}

int ind[N], outd[N];

void Build() {
    etot = 0;
    memset(hd, 0, sizeof(hd));
    for (int i = 1; i <= m; i++) {
        int z = ne[i];
        if ((x[z] != y[z]) && (x[z] != x[ne[i - 1]] || y[z] != y[ne[i - 1]])) {
            ind[y[z]]++;
            outd[x[z]]++;
            add_edge(x[z], y[z]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int t;
        while (scanf("%d", &t) == 1 && t) {
            add_edge(i, t);
            x[etot] = i;
            y[etot] = t;
            // printf("%d - %d -> %d\n", etot, x[etot], y[etot]);
        }
    }
    m = etot;
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    // 去重边
    Remove();
    // 重建图
    Build();
    int incnt = 0, outcnt = 0;
    for (int i = 1; i <= col; i++) {
        if (ind[i] == 0) {
            incnt++;
        } 
        if (outd[i] == 0) {
            outcnt++;
        }
    }
    printf("%d\n", incnt);
    if (col == 1) {
        printf("0\n");
    } else {
        printf("%d\n", max(incnt, outcnt));
    }       
    
    return 0;
}