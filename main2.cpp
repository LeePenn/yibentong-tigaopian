#include <bits/stdc++.h>
using namespace std;
const int MaxN = 1e5 + 5, MaxM = 1e6 + 5;

int n, m, mo;
int x[MaxM], y[MaxM];
int tot;
int de[MaxN], to[MaxM], hd[MaxN], nxt[MaxM];
int ue[MaxN];
int sz[MaxN];

void add_edge(int u, int v) {
    nxt[++tot] = hd[u];
    to[tot] = v;
    hd[u] = tot;
}

int num, top, col;
int dfn[MaxN], low[MaxN], st[MaxN], co[MaxN];

void Tarjan(int u) {
    dfn[u] = low[u] = ++num;
    st[++top] = u;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!co[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        co[u] = ++col;
        ++sz[col];
        while (st[top] != u) {
            co[st[top]] = col;
            sz[col]++;
            top--;
        }
        top--;
    }
}

int t, w;
int ans;
int e[MaxN];
int dis[MaxN];

bool rule(int a,int b) {
    if (x[a] != x[b]) {
        return x[a] < x[b];
    }
    return y[a] < y[b];
}

int nu[MaxM];

void Remove() {
    for (int i = 1; i <= m; i++) {
        nu[i] = i;
        x[i] = co[x[i]];
        y[i] = co[y[i]];
    }
    sort(nu + 1, nu + m + 1, rule);
}

void Reset() {
    for (int i = 1; i <= col; i++) {
        if (!de[i]) {
            ue[++w] = i;
            dis[i] = sz[i];
            e[i] = 1;
            if (dis[ans] < dis[i]) ans = i;
        }
    }
}

void Topo() {
    while (t < w) {
        int u = ue[++t];
        for (int i = hd[u]; i; i = nxt[i]) {
            int v = to[i];
            --de[v];
            if (dis[v] < dis[u] + sz[v]) {
                dis[v] = dis[u] + sz[v];
                e[v] = 0;
                if (dis[ans] < dis[v]) ans = v;
            }
            if (dis[v] == dis[u] + sz[v]) {
                e[v] = (e[v] + e[u]) % mo;
                if (!de[v]) ue[++w] = v;
            }
        }
    }
}

int anss;

void Ask() {
    for (int i = 1; i <= n; i++) {
        if (dis[i] == dis[ans]) {
            anss = (anss + e[i]) % mo;
        }
    }
}

void Build() {
    tot = 0;
    memset(hd, 0, sizeof(hd));
    for (int i = 1; i <= m; i++) {
        int z = nu[i];
        if ((x[z] != y[z]) && (x[z] != x[nu[i - 1]] || y[z] != y[nu[i - 1]])) {
            de[y[z]]++;
            add_edge(x[z], y[z]);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &mo);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x[i], &y[i]);
        add_edge(x[i], y[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) Tarjan(i);
    }
    
    Remove();
    Build();
    Reset();
    Topo();
    Ask();
    printf("%d\n%d\n", dis[ans], anss);

    return 0;
}