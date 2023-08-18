#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;
int n, m, mod;
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
    
    if (dfn[u] == low[u]) {
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

int x[M], y[M];

bool inline rule(int u, int v) {
    if (x[u] != x[v]) {
        return x[u] < x[v];
    } 
    return y[u] < y[v];
}

int nu[M];

void Remove() {
    for (int i = 1; i <= m; i++) {
        nu[i] = i;
        x[i] = co[x[i]];
        y[i] = co[y[i]];
    }
    sort(nu + 1, nu + m + 1, rule);
}

int ind[N];

void Build() {
    tot = 0;
    memset(hd, 0, sizeof(hd));
    for (int i = 1; i <= m; i++) {
        int z = nu[i];
        if ((x[z] != y[z]) && (x[z] != x[nu[i - 1]] || y[z] != y[nu[i - 1]])) {
            ++ind[y[z]];
            add_edge(x[z], y[z]);
        }
    }
}



int ans;

int tail, w, ue[N];
int e[N];
int dist[N];

void Reset() {
    for (int i = 1; i <= col; i++) {
        if (!ind[i]) {
            ue[++w] = i;
            e[i] = 1;
            dist[i] = sz[i];
            if (dist[ans] < dist[i]) ans = i;
        }
    }
}

void Topo() {
    tail = 1;
    while (tail <= w) {
        int u = ue[tail]; tail++;
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            ind[v]--;
            if (dist[v] < dist[u] + sz[v]) {
                dist[v] = dist[u] + sz[v];
                e[v] = 0;
                if (dist[ans] < dist[v]) ans = v;
            }
            if (dist[v] == dist[u] + sz[v]) {
                e[v] = (e[v] + e[u]) % mod;
            }
            if (!ind[v]) ue[++w] = v;
        }
    }
}

int anss;

void Ask() {
    for (int i = 1; i <= n; i++) {
        if (dist[i] == dist[ans]) {
            anss = (anss + e[i]) % mod;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &mod);
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
    
    printf("%d\n%d\n", dist[ans], anss);

    return 0;
}