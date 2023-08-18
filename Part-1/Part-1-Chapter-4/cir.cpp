#include <bits/stdc++.h>

using namespace std;

const int len = 500010;
const int N = 504;
const int INF = 100000000;
int n, m;
char c[N][N];
int d[N][N];
string line;

pair<int, int> q[len * 2];
int xDir[] = {-1, -1, 1, 1};
int yDir[] = {-1, 1, -1, 1};

bool inBoard(int x, int y) {
    return x >= 1 && x <= n + 1 && y >= 1 && y <= m + 1;
}

void bfs() {
    int hd = len, tail = len;
    q[tail] = make_pair(1, 1);
    d[q[tail].first][q[tail].second] = 0;
    while (hd <= tail) {
        int cur_r = q[hd].first, cur_c = q[hd].second, cur_d = d[cur_r][cur_c];
        hd++;
        for (int i = 0; i < 4; i++) {
            int nr = cur_r + xDir[i], nc = cur_c + yDir[i];
            if (!inBoard(nr, nc)) continue;
            int cost = 0;
            if (i == 0) {
                cost = c[nr][nc] == '\\' ? 0 : 1;
            } else if (i == 1) {
                cost = c[nr][nc - 1] == '\\' ? 1 : 0;
            } else if (i == 2) {
                cost = c[nr - 1][nc] == '\\' ? 1 : 0;
            } else {
                cost = c[nr - 1][nc - 1] == '\\' ? 0 : 1;
            }
            
            if (d[nr][nc] > cur_d + cost) {
                d[nr][nc] = cur_d + cost;
                
                if (hd == tail || d[nr][nc] > d[q[hd].first][q[hd].second]) {
                    tail++;
                    q[tail] = make_pair(nr, nc);
                } else {
                    hd--;
                    q[hd] = make_pair(nr, nc);
                }
            } 
        }
        
    }
}

int main() {
    // ios::sync_with_stdio(false);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        cin >> line;
        for (int j = 0; j < m; j++) {
            c[i][j + 1] = line[j];
        }
    }
    if ((n + m) % 2) {
        printf("NO SOLUTION\n");
        return 0;
    }
    
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) d[i][j] = INF;
    }
    
    bfs();
    if (d[n + 1][m + 1] == INF) printf("NO SOLUTION\n");
    else printf("%d\n", d[n + 1][m + 1]);
    

    return 0;
}