#include <bits/stdc++.h>

using namespace std;

const int N = 1002;
int n;
int a[N][N];
bool vis[N][N];
int down, up;
const int xDirs[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int yDirs[] = {0, 1, 1, 1, 0, -1, -1, -1};

bool in_board(int r, int c) {
    return r >= 1 && r <= n && c >= 1 && c <= n;
}

void bfs(int r, int c) {
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    vis[r][c] = true;
    bool isDown = false, isUp = false;
    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        int cur_r = cur.first, cur_c = cur.second, cur_h = a[cur_r][cur_c];
        // printf("%d %d %d\n", cur_r, cur_c, cur_h);
        for (int i = 0; i < 8; i++) {
            int nr = cur_r + xDirs[i], nc = cur_c + yDirs[i];
            // printf("nr = %d, nc = %d\n", nr, nc);
            if (!in_board(nr, nc)) continue;
            if (a[nr][nc] == cur_h && !vis[nr][nc]) {
                vis[nr][nc] = true;
                q.push(make_pair(nr, nc));
            } 
            if (a[nr][nc] > cur_h) isDown = true;
            else if (a[nr][nc] < cur_h) isUp = true;
            
            // printf("+++ %d %d\n", isDown, isUp);
        }
    }
    if (isDown && !isUp) down++;
    else if (!isDown && isUp) up++;
    else if (!isDown && !isUp) down++, up++;
    // printf("--- %d %d\n", up, down);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!vis[i][j]) bfs(i, j);
        }
    }
    
    printf("%d %d\n", up, down);
    
    return 0;
}