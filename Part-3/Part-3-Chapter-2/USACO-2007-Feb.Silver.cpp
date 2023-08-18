#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 5, M = 100000 + 10, INF = 1000;

int n, m, ed;
int g[N][N], fg[N][N];
int a, b, t;
priority_queue<pair<int, int> > q;
int dist[N], fdist[N];
bool vis[N];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) g[i][j] = g[j][i] = fg[i][j] = fg[j][i] = INF;
    }
    for (int i = 1; i <= n; i++) g[i][i] = fg[i][i] = 0;
    
}

void dijkstra() {
    q.push(make_pair(0, ed));
    memset(dist, 0x3f, sizeof(dist));
    dist[ed] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = 1; i <= n; i++) {
            if (i != u && g[u][i] < INF) {
                if (dist[i] > dist[u] + g[u][i]) {
                    dist[i] = dist[u] + g[u][i];
                    q.push(make_pair(-dist[i], i));
                }
            }
        }
    }
}

void dijkstra2() {
    memset(vis, 0, sizeof(vis));
    memset(fdist, 0x3f, sizeof(fdist));
    fdist[ed] = 0;
    // printf("%d\n", dist[st]);exit(0);
    q.push(make_pair(0, ed));
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = 1; i <= n; i++) {
            if (i != u && fg[u][i] < INF) {
                if (fdist[i] > fdist[u] + fg[u][i]) {
                    fdist[i] = fdist[u] + fg[u][i];
                    q.push(make_pair(-fdist[i], i));
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &ed);
    init();
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &a, &b, &t);
        g[a][b] = min(g[a][b], t);
        fg[b][a] = min(fg[b][a], t);
    }
    
    dijkstra();
    dijkstra2();
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dist[i] + fdist[i]);
    }
    printf("%d\n", ans);
    
    return 0;
}