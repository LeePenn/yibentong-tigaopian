#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 10, K = 100 + 5;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1}, dw[4] = {0, 0, 1, 1};
int dis[N][N][K];
int vis[N][N][K];
int hve[N][N];
struct point {
    int x, y, k;
    bool operator < (point other) const {
        if (x != other.x) {
            return x < other.x;
        }

        if (y != other.y) {
            return y < other.y;
        }

        return k < other.k;
    }
};
int main() {
    int n, k, a, b, c;
    scanf("%d%d%d%d%d", &n, &k, &a, &b, &c);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &hve[i][j]);
        }
    }

    memset(dis, 0x3f, sizeof(dis));
    dis[1][1][k] = 0;
    priority_queue<pair<int, point>> q;
    q.push({0, {1, 1, k}});

    while (! q.empty()) {
        point u = q.top().second;
        q.pop();

        if (vis[u.x][u.y][u.k]) {
            continue;
        }

        vis[u.x][u.y][u.k] = 1;

        if (hve[u.x][u.y] && u.k != k) {
            if (dis[u.x][u.y][u.k] + a < dis[u.x][u.y][k]) {
                dis[u.x][u.y][k] = dis[u.x][u.y][u.k] + a;
                q.push({- dis[u.x][u.y][k], {u.x, u.y, k}});
            }

            continue;
        }

        if (dis[u.x][u.y][u.k] + a + c < dis[u.x][u.y][k]) {
            dis[u.x][u.y][k] = dis[u.x][u.y][u.k] + a + c;
            q.push({- dis[u.x][u.y][k], {u.x, u.y, k}});
        }

        if (! u.k) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            int vx = u.x + dx[i], vy = u.y + dy[i], w = dw[i] * b;

            if (vx < 1 || vy < 1 || vx > n || vy > n) {
                continue;
            }

            if (dis[u.x][u.y][u.k] + w < dis[vx][vy][u.k - 1]) {
                dis[vx][vy][u.k - 1] = dis[u.x][u.y][u.k] + w;
                q.push({- dis[vx][vy][u.k - 1], {vx, vy, u.k - 1}});
            }
        }
    }

    int ans = dis[0][0][0];

    for (int i = 0; i <= k; i++) {
        ans = min(ans, dis[n][n][i]);
    }

    printf("%d", ans);
    return 0;
}