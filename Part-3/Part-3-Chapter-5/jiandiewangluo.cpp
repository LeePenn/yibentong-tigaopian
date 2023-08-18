#include <bits/stdc++.h>
using namespace std;

const int N = 3000 + 10, M = 8000 + 10;
int n, p, m;
int cost[N];
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
bool can_bride[N];
int scc_min_cost[N];
int ind[N], outd[N];
int x[M], y[M];
int ne[M];

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
        scc_min_cost[col] = min(scc_min_cost[col], cost[u]);
        while (st[top] != u) {
            co[st[top]] = col;
            scc_min_cost[col] = min(scc_min_cost[col], cost[st[top]]);
            top--;
        }
        top--;
    }
}

bool rule(int u, int v) {
    if (x[u] != x[v]) return x[u] < x[v];
    return y[u] < y[v];
}

void Remove() {
    for (int i = 1; i <= m; i++) {
        ne[i] = i;
        x[i] = co[x[i]];
        y[i] = co[y[i]];
    }
    sort(ne + 1, ne + m + 1, rule);
}

void Build() {
    etot = 0;
    memset(hd, 0, sizeof(hd));
    for (int i = 1; i <= m; i++) {
        int z = ne[i];
        if ((x[z] != y[z]) && (x[z] != x[ne[i - 1]] || y[z] != y[ne[i - 1]])) {
            add_edge(x[z], y[z]);
            ind[y[z]]++;
            outd[x[z]]++;
        }
    }
}

int tot_cost;

void Topo() {
    for (int i = 1; i <= col; i++) {
        if (ind[i] == 0) {
            tot_cost += scc_min_cost[i];
        }
    }
}

int main() {
    scanf("%d%d", &n, &p);
    memset(cost, 0x3f, sizeof(cost));
    for (int i = 1; i <= p; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        cost[a] = b;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x[i], &y[i]);
        add_edge(x[i], y[i]);
    }
    
    memset(scc_min_cost, 0x3f, sizeof(scc_min_cost));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i] && cost[i] < 0x3f3f3f3f) Tarjan(i);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            printf("NO\n%d\n", i);
            return 0;
        }
    }
    
    Remove();
    Build();
    Topo();
    
    // printf("%d %d\n", num, n);return 0;
    printf("YES\n%d\n", tot_cost);
    

    return 0;
}