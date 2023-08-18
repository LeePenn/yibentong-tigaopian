#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 100010, M = 300010, INF = 0x3f3f3f3f;

int n, k;
struct Edge {
    int v, nxt, c;
    Edge() { v = nxt = c = 0; }
    Edge(int V, int NXT, int C) {
        v = V;
        nxt = NXT;
        c = C;
    }
}edge[M];
int hd[N], tot;
int q[N * 10];

void add_edge(int u, int v, int type) {
    if (type == 1) {
        edge[++tot] = Edge(u, hd[v], 0);
        hd[v] = tot;
        edge[++tot] = Edge(v, hd[u], 0);
        hd[u] = tot;
    } else if (type == 2) {
        edge[++tot] = Edge(v, hd[u], 1);
        hd[u] = tot;
    } else if (type == 3) {
        edge[++tot] = Edge(u, hd[v], 0);
        hd[v] = tot;
    } else if (type == 4) {
        edge[++tot] = Edge(u, hd[v], 1);
        hd[v] = tot;
    } else {
        edge[++tot] = Edge(v, hd[u], 0);
        hd[u] = tot;
    }
}

LL dist[N];
bool vis[N];
int cnt[N];

bool SPFA() {
    memset(dist, -0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    int hh = 0, tt = 0;
    q[0] = 0;
    vis[0] = true;
    dist[0] = 0;
    
    while (hh <= tt) {
        // stack
        int u = q[tt]; tt--;
        vis[u] = false;
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            if (dist[u] + edge[i].c > dist[v]) {
                dist[v] = dist[u] + edge[i].c;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n + 1) {
                    return false;
                }
                if (!vis[v]) {
                    q[++tt] = v;
                    vis[v] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);
        add_edge(a, b, x);
    }
    
    for (int i = 1; i <= n; i++) {
        edge[++tot] = Edge(i, hd[0], 1);
        hd[0] = tot;
    }
    
    if (!SPFA()) {
        printf("-1\n");
    } else {
        LL ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += dist[i];
        }
        printf("%lld\n", ans);
    }
    
    

    return 0;
}