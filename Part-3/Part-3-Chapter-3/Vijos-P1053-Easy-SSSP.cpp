#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1000 + 3, M = 1e5 + 4;
const LL INF = 1000000000;
int n, m, s;
struct Edge {
    int v, nxt;
    LL w;
}edge[M];
int hd[N], tot;
bool NC;
LL dist[N];
int vis[N];

void add_edge(int u, int v, LL w) {
    edge[++tot].nxt = hd[u];
    edge[tot].v = v;
    edge[tot].w = w;
    hd[u] = tot;
}

void SPFA(int u, int root) {
    if (NC) return;
    vis[u] = root;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (dist[u] + edge[i].w < dist[v]) {
            dist[v] = dist[u] + edge[i].w;
            if (!vis[v]) SPFA(v, root);
            if (NC) return;
            else if (vis[v] == root) {
                NC = true;
                return;
            }
        }
    }
    
    vis[u] = 0;
}

void SPFA2() {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    vis[s] = true;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int u = que.front(); que.pop();
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dist[u] + edge[i].w < dist[v]) {
                dist[v] = dist[u] + edge[i].w;
                if (!vis[v]) {
                    que.push(v);
                    vis[v] = true;
                }
            }
        }
        vis[u] = false;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= m; i++) {
        int u, v;
        LL w;
        scanf("%d%d%lld", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    NC = false;
    for (int i = 1; i <= n; i++) {
        memset(dist, 0, sizeof(dist));
        memset(vis, 0, sizeof(vis));
        SPFA(i, i);
        if (NC) break;
    }
    
    if (NC) printf("-1\n");
    else {
        SPFA2();
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INF) printf("NoPath\n");
            else printf("%lld\n", dist[i]);
        }
    }

    return 0;
}