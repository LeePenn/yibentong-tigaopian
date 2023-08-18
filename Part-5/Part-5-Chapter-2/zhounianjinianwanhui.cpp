#include <bits/stdc++.h>
using namespace std;
const int N = 6000 + 10;
int n, h[N];
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
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
    }
    int u, v;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void DP(int u, int fa) {
    f[u][0] = 0;
    f[u][1] = h[u];
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        DP(v, u);
        f[u][0] += max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    Read();
    
    DP(1, 0);
    
    printf("%d\n", max(f[1][0], f[1][1]));
    
    return 0;
}