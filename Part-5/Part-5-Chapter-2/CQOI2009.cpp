#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, INF = 0x3f3f3f3f;
int n, m, c[N];
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[N << 1];
int hd[N], etot;
int f[N][2];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d%d", &m, &n);
    int x;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
    }
    int u, v;
    for (int i = 1; i < m; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
    
    for (int i = 1; i <= m; ++i) {
        f[i][0] = f[i][1] = 1;
        if (i <= n) {
            f[i][1 - c[i]] = INF;
        }
    }
}

void DP(int u, int fa) {
    if (u <= n) return;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        DP(v, u);
        f[u][0] += min(f[v][0] - 1, f[v][1]);
        f[u][1] += min(f[v][1] - 1, f[v][0]);
    }
}

int main() {
    Read();
    
    DP(n + 1, 0);
    
    printf("%d\n", min(f[n + 1][0], f[n + 1][1]));
    
    return 0;
}