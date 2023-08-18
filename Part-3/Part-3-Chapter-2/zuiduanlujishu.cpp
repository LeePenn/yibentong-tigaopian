#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10, MOD = 100003;

int n, m;
int x, y, z;
int hd[N], nx[M << 1], to[M << 1], w[M << 1], tot;
int dist[N];
bool vis[N];
int ans[N];
priority_queue<pair<int, int> > heap;

void add_edge(int x, int y, int z) {
    nx[++tot] = hd[x];
    to[tot] = y;
    w[tot] = z;
    hd[x] = tot;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    memset(ans, 0, sizeof(ans));
    ans[1] = 1;
    dist[1] = 0;
    heap.push(MP(0, 1));
    while (!heap.empty()) {
        int u = heap.top().second, d = heap.top().first; heap.pop();
        // if (vis[u]) continue;
        for (int i = hd[u]; i; i = nx[i]) {
            int v = to[i];
            if (dist[v] > dist[u] + w[i]) {
                dist[v] = dist[u] + w[i];
                ans[v] = ans[u];
                // printf("$$$%d %d %d %d\n", u, v, dist[v], ans[v]);
                heap.push(MP(-dist[v], v));
            } else if (dist[v] == dist[u] + w[i]) {
                ans[v] += ans[u];
                ans[v] %= MOD;
                // printf("###%d %d %d %d\n", u, v, dist[v], ans[v]);
            }
        }
    }
}
    
int main() {    
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        add_edge(x, y, 1); add_edge(y, x, 1);
    }
    dijkstra();
    for (int i = 1; i <= n; i++) {
        if (dist[i] == 0x3f3f3f3f) printf("0\n");
        else printf("%d\n", ans[i]);
    }
    
    return 0;
}