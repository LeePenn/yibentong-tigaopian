#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 4e5 + 10;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
// etot不能从1开始，否则，if i == 1, i/2 = 0 !!
int hd[N], etot = 1;
int ne[N];
int in[N], out[N];
int type;
int n, m;
int ans[M], cnt;
bool vis[M];

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
    in[v]++;
    out[u]++;
}

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
        if (type == 2) {
            ans[++cnt] = i - 1;
        } else {
            // etot 从1开始
            if (i % 2) {
                ans[++cnt] = -(i >> 1);
            } else {
                ans[++cnt] = i >> 1;
            }
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
    }
    
    for (int i = 1; i <= n; i++) {
        if (type == 1 && in[i] % 2) {
            printf("NO\n");
            return 0;
        }
        if (type == 2 && in[i] != out[i]) {
            printf("NO\n");
            return 0;
        }
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

    return 0;
}
