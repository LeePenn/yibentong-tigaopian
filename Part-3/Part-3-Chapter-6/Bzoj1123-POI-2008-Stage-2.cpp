#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 1e6 + 10;
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

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], dfstime;
bool cut[N];
LL sz[N];
LL ans[N];
int root;

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    LL sum = 0;
    sz[u] = 1;
    ans[u] = 0;
    int c = 0;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            c++;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
            if (dfn[u] <= low[v]) {
                if (u != root || c > 1) {
                    cut[u] = true;
                }
                ans[u] += sz[v] * (n - sz[v]);
                sum += sz[v];
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    
    if (cut[u]) {
        ans[u] += (n - sum - 1) * (sum + 1) + n - 1;
    } else {
        ans[u] = 2 * (n - 1);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i; 
            Tarjan(i);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}