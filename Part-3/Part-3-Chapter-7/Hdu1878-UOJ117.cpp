#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1e6 + 10;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot = 1;
int type, n, m;
int in[N], out[N];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

bool Euler_loop() {
    for (int i = 1; i <= n; i++) {
        if (type == 1) {
            if ((in[i] + out[i]) % 2 != 0) return false;
        } else {
            if (in[i] != out[i]) return false;
        }
    }
    return true;
}

bool vis[M];
int ans[M], cnt;

void dfs(int u) {
    for (int i = hd[u]; i; i = hd[u]) {
        if (vis[i]) {
            hd[u] = edge[i].nxt;
            continue;
        }
        
        vis[i] = true;
        if (type == 1) vis[i ^ 1] = true;
        int v = edge[i].v;
        dfs(v);
        if (type == 1) {
            if (i % 2) {
                ans[++cnt] = -(i >> 1);
            } else {
                ans[++cnt] = i >> 1;
            }
        } 
        if (type == 2) {
            ans[++cnt] = i - 1;
        }
    }
}

int main() {
    scanf("%d", &type);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        if (type == 1) add_edge(v, u);
        in[v]++, out[u]++;
    }
    
    if (!Euler_loop()) {
        printf("NO\n");
        return 0;
    }
    
    for (int i = 1; i <= n; i++) {
        if (hd[i]) {
            dfs(i);
            break;
        }
    }
    
    if (cnt < m) {
        printf("NO\n");
        return 0;
    }
    
    printf("YES\n");
    for (int i = cnt; i; i--) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}