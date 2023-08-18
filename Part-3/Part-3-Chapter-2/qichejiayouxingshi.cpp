#include <bits/stdc++.h>
#define MP make_pair
using namespace std;

const int N = 100 + 4, K = 10 + 3;
int n, k, A, B, C;
struct St {
    int x, y, k;
    bool operator <(const St &rh) const {
        if (x != rh.x) return x < rh.x;
        if (y != rh.y) return y < rh.y;
        return k < rh.k;
    }
}a[N * N * K];
priority_queue<pair<int, St> > heap;
int g[N][N];
int ans;
int dist[N][N][K];
bool vis[N][N][K];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, dw[4] = {0, 0, 1, 1};

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1][1][k] = 0;
    heap.push(MP(0, (St){1, 1, k}));
    while (!heap.empty()) {
        St u = heap.top().second; heap.pop();
        if (vis[u.x][u.y][u.k]) continue;
        vis[u.x][u.y][u.k] = 1;
        
        if (g[u.x][u.y] && u.k != k) {
            if (dist[u.x][u.y][u.k] + A < dist[u.x][u.y][k]) {
                dist[u.x][u.y][k] = dist[u.x][u.y][u.k] + A;
                heap.push(MP(-dist[u.x][u.y][k], (St){u.x, u.y, k}));
            }
            continue;
        }
        if (dist[u.x][u.y][u.k] + A + C < dist[u.x][u.y][k]) {
            dist[u.x][u.y][k] = dist[u.x][u.y][u.k] + A + C;
            heap.push(MP(-dist[u.x][u.y][k], (St){u.x, u.y, k}));
        }
        
        if (u.k == 0) continue;
        
        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i], ny = u.y + dy[i], w = dw[i] * B;
            if (nx < 1 || ny < 1 || nx > n || ny > n) continue;
            if (dist[nx][ny][u.k - 1] > dist[u.x][u.y][u.k] + w) {
                dist[nx][ny][u.k - 1] = dist[u.x][u.y][u.k] + w;
                heap.push(MP(-dist[nx][ny][u.k - 1], (St){nx, ny, u.k - 1}));
            }
        }
    }
}

int main() {
    cin >> n >> k >> A >> B >> C;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> g[i][j];
    }
    // printf("%d\n", tot);return 0;
    dijkstra();
    ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++) {
        if (dist[n][n][i] < ans) ans = dist[n][n][i];
    }
    printf("%d\n", ans);

    return 0;
}