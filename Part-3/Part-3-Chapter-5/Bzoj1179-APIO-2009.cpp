#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 5e5 + 10, M = 5e5 + 10;
int n, m, s, p;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
bool cafe[N];
LL mon[N];
int x[M], y[M];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], tim, st[N], top, co[N], col;
LL sum[N];

void Tarjan(int u) {
    low[u] = dfn[u] = ++tim;
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
        sum[col] += mon[u];
        while (st[top] != u) {
            co[st[top]] = col;
            sum[col] += mon[st[top]];
            top--;
        }
        top--;
    }
}

int ne[M];

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
        }
    }
}

bool vis[N];
bool ne_cafe[N];
LL ans;
LL sum_copy[N];
LL dist[N];

void Dfs(int u, LL cur) {
    if (dist[u] > cur + sum_copy[u]) return;
    
    dist[u] = cur + sum_copy[u];
    if (ne_cafe[u] && cur + sum_copy[u] > ans) {
        ans = cur + sum_copy[u];
    }
    cur += sum_copy[u];
    sum_copy[u] = 0;
    vis[u] = true;
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!vis[v]) {
            Dfs(v, cur);
        }
    }
    cur -= sum[u];
    sum_copy[u] = sum[u];
    vis[u] = false;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x[i], &y[i]);
        add_edge(x[i], y[i]);
    }
    for (int i = 1; i <= n; i++) {
        LL c;
        scanf("%lld", &c);
        mon[i] = c;
    }
    
    scanf("%d%d", &s, &p);
    for (int i = 1; i <= p; i++) {
        int u;
        scanf("%d", &u);
        cafe[u] = true;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    
    Remove();
    Build();
    for (int i = 1; i <= n; i++) {
        if (cafe[i]) {
            ne_cafe[co[i]] = true;
        }
    }
    // printf("%d\n", col);
    // return 0;
    
    // printf("%lld\n", sum[co[s]]);
    // return 0;
    memcpy(sum_copy, sum, sizeof(sum_copy));
    Dfs(co[s], 0);
    
    printf("%lld\n", ans);

    return 0;
}