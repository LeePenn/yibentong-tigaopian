#include <bits/stdc++.h>

using namespace std;

const int N = 15;
int cp[N][11][11], b[11][11], n;
int lx, ly, rx, ry, c, maxx, maxy, rec[11][11], tot;
int dep;
bool v[N][N];

void init(int x1, int y1, int x2, int y2, int c) {
    ++tot;
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            b[i][j] = c;
            rec[i][j] = tot;
        }
    }
}

bool check() {
    for (int i = 0; i <= maxx; i++) {
        for (int j = 0; j <= maxy; j++) {
            if (b[i][j] != 0) return false;
        }
    }
    return true;
}

void paint(int x, int y) {
    int i, j;
    int cc = b[x][y];
    for (j = 0; j <= maxy; j++) {
        i = 0;
        while (i <= maxx && (b[i][j] == cc || b[i][j] == 0)) {
            b[i][j] = 0;
            i++;
        }
    }
    
    /* for (int i = 0; i <= maxx; i++) {
        for (int j = 0; j <= maxy; j++) cout << b[i][j] << ' ';
        cout << endl;
    }
    cout << endl; */
    // exit(0);
}

bool dfs(int t, int pre) {
    if (check()) return true;
    if (t >= dep) return false;
    
    int i, j;
    memset(v[t], 0, sizeof(v[t]));
    for (j = 0; j <= maxy; j++) {
        for (i = 0; i <= maxx; i++) {
            if (b[i][j] > 0) {
                int cc = b[i][j];
                if (!v[t][rec[i][j]]) {
                    v[t][rec[i][j]] = true;
                    memcpy(cp[t], b, sizeof(cp[t]));
                    paint(i, j);
                    if (pre == cc) {
                        if (dfs(t, pre)) return true;
                    } else {
                        if (dfs(t + 1, cc)) return true;
                    }
                    
                    memcpy(b, cp[t], sizeof(b));
                }
                break;
            }
        }
        
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d%d", &lx, &ly, &rx, &ry, &c);
        // paint init
        init(lx, ly, rx, ry, c);
        maxx = max(maxx, rx);
        maxy = max(maxy, ry);
    }
    
    
    /* memcpy(cp[0], b, sizeof(cp));
    for (int i = 0; i <= maxx; i++) {
        for (int j = 0; j <= maxy; j++) {
            cout << cp[0][i][j] << ' ';
        }
        cout << endl;
    } */
    
    for (dep = 1; ; dep++) if (dfs(0, 0)) break;
    
    printf("%d\n", dep);
    return 0;
}