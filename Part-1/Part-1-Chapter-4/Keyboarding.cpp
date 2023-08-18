#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int L = 10004;
int n, m;
struct Keyboard {
    int x, y;
}nx[N][N][4];
char s[N][N];
char ed[L];
struct Node {
    int x, y, idx, dist;   
};
int vis[N][N];
// bool vis[N][N][L];
int len;

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // up
            for (int k = i - 1; k >= 1; k--) {
                if (s[i][j] != s[k][j]) {
                    nx[i][j][0] = Keyboard({k, j});
                    break;
                }
            }
            // right
            for (int k = j + 1; k <= m; k++) {
                if (s[i][j] != s[i][k]) {
                    nx[i][j][1] = Keyboard({i, k});
                    break;
                }
            }
            // down
            for (int k = i + 1; k <= n; k++) {
                if (s[i][j] != s[k][j]) {
                    nx[i][j][2] = Keyboard({k, j});
                    break;
                }
            }
            // left
            for (int k = j - 1; k >= 1; k--) {
                if (s[i][j] != s[i][k]) {
                    nx[i][j][3] = Keyboard({i, k});
                    break;
                }
            }
        }
    }
}

void bfs() {
    queue<Node> q;
    q.push(Node({1, 1, 1, 0}));
    len = strlen(ed + 1);
    // memset(vis, 0, sizeof(vis));
    // vis[1][1][1] = true;
    memset(vis, -1, sizeof(vis));
    vis[1][1] = 0;
   
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y, idx = q.front().idx, dist = q.front().dist;
        q.pop();
        // push, u cannot continue in this condition
        if (s[x][y] == ed[idx]) {
            if (idx == len) {
                printf("%d\n", dist + 1);
                return;
            }
            q.push(Node({x, y, idx + 1, dist + 1}));
        }
        
        for (int i = 0; i < 4; i++) {
            Keyboard nn = nx[x][y][i];
            int cur_x = nn.x, cur_y = nn.y;
            if (cur_x == 0) continue;
            // if (!vis[cur_x][cur_y][idx]) {
            //     vis[cur_x][cur_y][idx] = true;
            //     q.push(Node({cur_x, cur_y, idx, dist + 1}));
            // }  
            // or
            if (vis[cur_x][cur_y] < idx) {
                vis[cur_x][cur_y] = idx;
                q.push(Node({cur_x, cur_y, idx, dist + 1}));
            }   
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
    }
    scanf("%s", ed + 1);
    ed[strlen(ed + 1) + 1] = '*';
    
    init();
    
    bfs();
    

    return 0;
}