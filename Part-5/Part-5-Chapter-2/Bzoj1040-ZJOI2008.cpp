#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, val[N];
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[N << 1];
int hd[N], etot;
int fa[N], root;
bool vis[N];
LL f[N][2];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int y;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &val[i], &y);
        add_edge(y, i);
        fa[i] = y;
    }
}

void dfs(int u) {
    if (vis[u]) {
        root = u;
    } else {
        vis[u] = 1;
        dfs(fa[u]);
    }
}

void DP(int u, int pa) {
    f[u][0] = 0;
    f[u][1] = val[u];
    vis[u] = 1;
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        
        if (v != root) {
            DP(v, u);
            f[u][0] += max(f[v][0], f[v][1]);
            f[u][1] += f[v][0];
        } else {
            f[u][1] = -INF;
        }
    }
}   

void Work() {
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        
        root = -1;
        dfs(i);
        
        if (root == -1) continue;
        
        DP(root, -1);
        
        LL v1 = max(f[root][0], f[root][1]);
        root = fa[root];
        DP(root, -1);
        ans += max(v1, max(f[root][0], f[root][1]));
    }
    
    printf("%lld\n", ans);
}

/*
先dfs找到环，删去环上一条边，以删去的边的两个端点为根分别跑dp，加上较大值，再继续对下一个环做同样的操作
*/
int main() {
    Read();
    
    Work();
    
    return 0;
}