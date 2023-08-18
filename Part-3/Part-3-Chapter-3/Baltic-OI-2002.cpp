#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 5, M = 3e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, e;
struct Edge {
    int v, nxt;
    int time, cost;
}edge[M];
int hd[N], tot;
struct DIST {
    int sum, cost;
}dist[N][M];
bool vis[N][M];
struct mm {
    int pos, time;
};
queue<mm> q;
int maxTime;

void add_edge(int u, int v, int time, int cost) {
    edge[++tot].nxt = hd[u];
    edge[tot].v = v;
    edge[tot].time = time;
    edge[tot].cost = cost;
    hd[u] = tot;
}

void dij() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) 
            dist[i][j].sum = 0, dist[i][j].cost = INF;
    }
    dist[s][0].sum = 1;
    dist[s][0].cost = 0;
    memset(vis, 0, sizeof(vis));
    vis[s][0] = true;
    mm st;
    st.pos = s;
    st.time = 0;
    q.push(st);
    while (!q.empty()) {
        mm cur = q.front(); q.pop();
        int u = cur.pos, time = cur.time;
        for (int i = hd[u]; i; i = edge[i].nxt) {
            int v = edge[i].v, t = edge[i].time, c = edge[i].cost;
            if (time + t > maxTime + 1) continue;
            if (dist[u][time].cost + c < dist[v][time + t].cost) {
                dist[v][time + t].cost = dist[u][time].cost + c;
                dist[v][time + t].sum = 1;
                if (!vis[v][time + t]) {
                    mm vv;
                    vv.pos = v;
                    vv.time = time + t;
                    q.push(vv);
                    vis[v][time + t] = true;
                }
            }
        }
        
        vis[u][time] = false;
    }
    
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 1; i <= m; i++) {
        int u, v, time, cost;
        scanf("%d%d%d%d", &u, &v, &time, &cost);
        add_edge(u, v, time, cost); add_edge(v, u, time, cost);
    }
    maxTime = (n - 1) * 100;
    dij();
    
    int ans = 0, maxCost = INF;
    for (int i = 0; i <= maxTime + 5; i++) {
        if (dist[e][i].sum == 0) continue;
        if (dist[e][i].cost < maxCost) {
            ans++;
            maxCost = dist[e][i].cost;
        }
    }
    printf("%d\n", ans);
    
    return 0;
}