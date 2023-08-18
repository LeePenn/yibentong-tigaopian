#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 10, P = 2000 + 10;

int n, p, k;
struct E {
    int nxt, to, c;
}e[P * 2];
int hd[N], tot;
priority_queue<pair<int, int> > q;
int dist[N];
bool vis[N];

void add_edge(int x, int y, int z) {
    e[++tot].to = y;
    e[tot].c = z;
    e[tot].nxt = hd[x];
    hd[x] = tot;
}

bool check(int mid) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(0, 1));
    dist[1] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = hd[u]; i; i = e[i].nxt) {
            int v = e[i].to, c = e[i].c; 
            if (c > mid) c = 1;
            else c = 0;
            if (dist[v] > dist[u] + c) {
                dist[v] = dist[u] + c;
                q.push(make_pair(-dist[v], v));
            }
        }
    }
    return dist[n] <= k;
    
}

int main() {
    scanf("%d%d%d", &n, &p, &k);
    int x, y, z;
    for (int i = 1; i <= p; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z); add_edge(y, x, z);
    }
    int l = 0, r = 99999999;
    int ans = 99999999;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    
    if (ans == 99999999) printf("-1\n");
    else printf("%d\n", ans);
    
    return 0;
}