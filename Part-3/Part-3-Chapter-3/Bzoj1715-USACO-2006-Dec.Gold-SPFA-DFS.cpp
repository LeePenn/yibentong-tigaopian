#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 4, M = 6000;

int n, m1, m2, T;
struct Edge {
    int v, nxt;
    int time;
}edge[M];
int hd[N], tot;
int dist[N];
int vis[N];
bool NC;

void add_edge(int u, int v, int time) {
    edge[++tot].nxt = hd[u];
    edge[tot].v = v;
    edge[tot].time = time;
    hd[u] = tot;
}

void SPFA(int u, int root) {
    if (NC) return;
    vis[u] = root;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v, time = edge[i].time;
        if (dist[u] + time < dist[v]) {
            dist[v] = dist[u] + time;
            if (!vis[v]) {
                SPFA(v, root);
            }
            if (NC) return;
            else if (vis[v] == root) {
                NC = true;
                return;
            }
        }
    }
    
    vis[u] = 0;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m1, &m2);
        tot = 0;
        memset(hd, 0, sizeof(hd));
        for (int i = 1; i <= m1; i++) {
            int u, v, time;
            scanf("%d%d%d", &u, &v, &time);
            add_edge(u, v, time); add_edge(v, u, time);
        }
        for (int i = 1; i <= m2; i++) {
            int u, v, time;
            scanf("%d%d%d", &u, &v, &time);
            add_edge(u, v, -time);
        }
        
        NC = false;
        for (int i = 1; i <= n; i++) {
            memset(vis, 0, sizeof(vis));
            memset(dist, 0, sizeof(dist));
            SPFA(i, i);
            if (NC) break;
        }
        if (NC) printf("YES\n");
        else printf("NO\n");
    }
    

    return 0;
}