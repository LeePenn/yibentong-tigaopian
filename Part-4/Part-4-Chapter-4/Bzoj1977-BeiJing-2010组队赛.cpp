#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 3e5 + 10, LOGN = 25;

int n, m;
struct Edge {
    int u, v, w;
    Edge() { u = v = w; }
    Edge(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
    }
    bool operator < (const Edge &rh) const {
        return w < rh.w;
    }
}edge[M];
struct Edge2 {
    int nxt, v, w;
    Edge2() { nxt = v = w = 0; }
    Edge2(int _nxt, int _v, int _w) {
        nxt = _nxt;
        v = _v;
        w = _w;
    }
}edge2[M << 1];

int hd[N], etot;
int dep[N], f[N][LOGN];
int fa[N];
bool used[M];
int fm[N][LOGN], sm[N][LOGN];
LL sum;

void add_edge(int u, int v, int w) {
    edge2[++etot] = Edge2(hd[u], v, w);
    hd[u] = etot;
}

void Read() {
    scanf("%d%d", &n, &m);
    int x, y, z;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        edge[i] = Edge(x, y, z);
    }
}

void Dfs1(int u, int pa) {
    dep[u] = dep[pa] + 1;
    for (int i = 0; i <= 20; i++) {
        f[u][i + 1] = f[f[u][i]][i];
        int ff = f[u][i];
        fm[u][i + 1] = max(fm[u][i], fm[ff][i]);
        sm[u][i + 1] = max(sm[u][i], sm[ff][i]);
        
        if (fm[u][i] > fm[ff][i]) {
            sm[u][i + 1] = max(fm[ff][i], sm[u][i + 1]);
        }
        if (fm[u][i] < fm[ff][i]) {
            sm[u][i + 1] = max(fm[u][i], sm[u][i + 1]);
        }
    }
    
    for (int i = hd[u]; i; i = edge2[i].nxt) {
        int v = edge2[i].v;
        if (v == pa) continue;
        fm[v][0] = edge2[i].w;
        f[v][0] = u;
        Dfs1(v, u);
    }
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void Kruskal() {
    for (int i = 1; i <= n; i++) fa[i] = i;
    
    sort(edge + 1, edge + m + 1);
    int tot = 0;
    for (int i = 1; i <= m; i++) {
        int u = find(edge[i].u);
        int v = find(edge[i].v);
        if (u != v) {
            fa[v] = u;
            sum += edge[i].w;
            add_edge(u, v, edge[i].w); add_edge(v, u, edge[i].w);
            tot++;
            used[i] = true;
        }
        if (tot == n - 1) break;
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; ~i; i--) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
        if (u == v) return u;
    }
    
    for (int i = 20; ~i; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

int Findmax(int u, int lca, int val) {
    int ans = 0;
    for (int i = log2(dep[u] - dep[lca]) + 1; i >= 0; i--) {
        if (dep[f[u][i]] >= dep[lca]) {
            if (fm[u][i] == val) {
                ans = max(ans, sm[u][i]);
            } else {
                ans = max(ans, fm[u][i]);
            }
            u = f[u][i];
        }
    }
    
    return ans;
}

void calc() {
    LL ans = 1e18;
    for (int i = 1; i <= m; i++) {
        if (used[i]) continue;
        
        int u = edge[i].u, v = edge[i].v, w = edge[i].w;
        int lca = LCA(u, v);
        int a1 = Findmax(u, lca, w);
        int a2 = Findmax(v, lca, w);
        if (max(a1, a2) != w) {
            ans = min(ans, sum - max(a1, a2) + w);
        }
    }
    printf("%lld\n", ans);
    return;
}

int main() {
    Read();
    
    Kruskal();
    
    Dfs1(1, 0);
    
    calc();

    return 0;
}