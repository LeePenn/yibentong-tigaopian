#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100 + 4, INF = 0x3f3f3f3f;

int n, m;
int d[N][N], a[N][N];
int x, y, z;
int pos[N][N];
vector<int> path;

void get_path(int x, int y) {
    if (pos[x][y] == 0) return;
    get_path(x, pos[x][y]);
    path.push_back(pos[x][y]);
    get_path(pos[x][y], y);
}
    
int main() {    
    scanf("%d %d", &n, &m);
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        d[x][y] = d[y][x] = min(d[x][y], z);
    }   
    memcpy(a, d, sizeof(a));
    int ans = INF;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if ((LL)d[i][j] + a[i][k] + a[j][k] < ans)  {
                    ans = d[i][j] + a[i][k] + a[j][k];
                    path.clear();
                    path.push_back(i);
                    get_path(i, j);
                    path.push_back(j);
                    path.push_back(k);
                }
            }
        }
    
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
    if (ans == INF) printf("No solution.\n"), exit(0);
    
    for (int i = 0; i < path.size(); i++) {
        printf("%d ", path[i]);
    }
    printf("\n");

    return 0;
}