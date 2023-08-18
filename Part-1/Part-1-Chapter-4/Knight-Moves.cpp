#include <bits/stdc++.h>

using namespace std;

const int MAX = 303;
int T;
int L, sx, sy, ex, ey; 
struct MOV {
    int x, y, step;
}q[2][MAX * MAX * 2];
int d0[MAX][MAX], d1[MAX][MAX];
const int xDirs[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int yDirs[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool in_board(int x, int y) {
    return x >= 1 && x <= L && y >= 1 && y <= L;
}

void bfs() {
    int h0 = 0, t0 = 1, h1 = 0, t1 = 1;
    q[0][1].x = sx, q[0][1].y = sy, q[0][1].step = 0;
    q[1][1].x = ex, q[1][1].y = ey, q[1][1].step = 0;
    memset(d0, -1, sizeof(d0)); memset(d1, -1, sizeof(d1));
    d0[sx][sy] = 0, d1[ex][ey] = 0;
    
    int cnt0 = 1, cnt1 = 1;
    while (h0 < t0 && h1 < t1) {
        if (cnt0 <= cnt1) {
            int cur_cnt0 = 0;
            while (cnt0--) {
                h0++;
                MOV p0 = q[0][h0];
                int cur_x0 = p0.x, cur_y0 = p0.y, cur_step0 = p0.step;
                if (d1[cur_x0][cur_y0] != -1) {
                    printf("%d\n", d1[cur_x0][cur_y0] + cur_step0);
                    return;
                }
                
                for (int i = 0; i < 8; i++) {
                    int nx0 = cur_x0 + xDirs[i], ny0 = cur_y0 + yDirs[i];
                    if (!in_board(nx0, ny0)) continue;
                    
                    if (d0[nx0][ny0] == -1) {
                        d0[nx0][ny0] = cur_step0 + 1;
                        t0++;
                        q[0][t0].x = nx0, q[0][t0].y = ny0, q[0][t0].step = cur_step0 + 1;
                        cur_cnt0++;
                    }
                }
            }
            cnt0 = cur_cnt0;
        } else {
            int cur_cnt1 = 0;
            while (cnt1--) {
                h1++;
                MOV p1 = q[1][h1];
                int cur_x1 = p1.x, cur_y1 = p1.y, cur_step1 = p1.step;
                if (d0[cur_x1][cur_y1] != -1) {
                    printf("%d\n", d0[cur_x1][cur_y1] + cur_step1);
                    return;
                }
                
                for (int i = 0; i < 8; i++) {
                    int nx1 = cur_x1 + xDirs[i], ny1 = cur_y1 + yDirs[i];
                    if (!in_board(nx1, ny1)) continue;
                    if (d1[nx1][ny1] == -1) {
                        d1[nx1][ny1] = cur_step1 + 1;
                        t1++;
                        q[1][t1].x = nx1, q[1][t1].y = ny1, q[1][t1].step = cur_step1 + 1;
                        cur_cnt1++;
                    }
                }
            }
            cnt1 = cur_cnt1;
        }
    }
}

int main() {
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d %d %d", &L, &sx, &sy, &ex, &ey);
        bfs();
    }
    

}