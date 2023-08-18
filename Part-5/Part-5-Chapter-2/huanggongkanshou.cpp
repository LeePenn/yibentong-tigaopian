#include <bits/stdc++.h>
using namespace std;
const int N = 1500 + 10;

int n;
int cost[N];
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[N << 1];
int hd[N], etot;
int rt; 
bool vis[N];
int f[N][3];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int u, k, v;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &u);
        scanf("%d%d", &cost[u], &k);
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &v);
            add_edge(u, v); add_edge(v, u);
            vis[v] = 1;
        }
    }
    
    rt = 1; 
    while (vis[rt]) {
        rt++;
    }
}

void DP(int u, int fa) {
    f[u][2] = cost[u];
    int d = 0x3f3f3f3f;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        DP(v, u);
        f[u][0] += min(f[v][1], f[v][2]);
        f[u][1] += min(f[v][1], f[v][2]);
        d = min(d, f[v][2] - min(f[v][1], f[v][2]));
        f[u][2] += min(f[v][0], min(f[v][1], f[v][2]));
    }
    f[u][1] += d;
}

int main() {
    Read();
    
    DP(rt, -1);
    
    printf("%d\n", min(f[rt][1], f[rt][2]));

    return 0;
}