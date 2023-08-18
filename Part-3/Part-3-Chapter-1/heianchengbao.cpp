#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1004, INF = 199311170;
const LL P = (1LL << 31) - 1;
int n, m;
int g[N][N];
int x, y, z;
int dist[N], idx[N];
bool vis[N];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) g[i][j] = g[j][i] = INF;
    }
    for (int i = 1; i <= n; i++) g[i][i] = 0;
}

void build_edge(int x, int y, int z) {
    g[x][y] = z; g[y][x] = z;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        int k = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j]) {
                if (k == 0 || dist[j] < dist[k]) {
                    k = j;
                }
            }
        }
        vis[k] = true;
        for (int j = 1; j <= n; j++) {
            if (!vis[j]) {
                dist[j] = min(dist[j], dist[k] + g[j][k]);
            }
        }
    }
}

bool cmp(const int &a, const int &b) {
    return dist[a] < dist[b];
}

void work() {
    for (int i = 1; i <= n; i++) idx[i] = i;
    sort(idx + 1, idx + n + 1, cmp);
    
    LL ans = 1;
    for (int i = 2; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j < i; j++) {
            if (dist[idx[i]] == dist[idx[j]] + g[idx[i]][idx[j]]) cnt++;
        }
        ans *= cnt;
        ans %= P;
    }
    printf("%lld\n", ans);
}

int main() {
    cin >> n >> m;
    init();
    
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> z;
        build_edge(x, y, z); build_edge(y, x, z);
    }
    dijkstra();
    work();
    
    // for (int i = 1; i <= n; i++) printf("%d ", dist[i]);

    return 0;
}