#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[N << 1];
int hd[N], etot;
int d1[N], d2[N];
bool vis[N];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void DP(int u, int fa) {
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        DP(v, u);
        if (d1[v] + 1 > d1[u]) {
            d2[u] = d1[u];
            d1[u] = d1[v] + 1;
        } else if (d1[v] + 1 > d2[u]) {
            d2[u] = d1[v] + 1;
        }
    }
}

void add_path(int u, int fa, int d) {
    vis[u] = true;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        if (d1[v] + 1 == d) {
            add_path(v, u, d1[v]);
        }
    }
}

int main() {
    Read();
    
    DP(0, -1);
    
    int maxx = 0;
    for (int i = 0; i < n; ++i) {
        if (d1[i] + d2[i] > maxx) maxx = d1[i] + d2[i];
    }
    
    for (int i = 0; i < n; ++i) {
        if (d1[i] + d2[i] == maxx) {
            add_path(i, -1, d1[i]);
            add_path(i, -1, d2[i]);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (vis[i]) printf("%d\n", i);
    }

    return 0;
}