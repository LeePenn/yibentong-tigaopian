#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 4, M = 6000;

int n, m1, m2, T;
struct Edge {
    int u, v;
    int time;
}edge[M];
int tot;
int dist[N];
int vis[N];
bool NC;

void add_edge(int u, int v, int time) {
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].time = time;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m1, &m2);
        tot = 0;
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
        
        
        memset(dist, 0x3f, sizeof(dist));
        dist[1] = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= tot; j++) {
                int u = edge[j].u, v = edge[j].v;
                if (dist[u] + edge[j].time < dist[v]) {
                    dist[v] = dist[u] + edge[j].time;
                }
            }
        }
        NC = false;
        for (int i = 1; i <= tot; i++) {
            int u = edge[i].u, v = edge[i].v;
            if (dist[u] + edge[i].time < dist[v]) {
                NC = true;
                break;
            }
        }
        
        
        if (NC) printf("YES\n");
        else printf("NO\n");
    }
    

    return 0;
}