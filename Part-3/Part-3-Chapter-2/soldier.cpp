#include <bits/stdc++.h>
using namespace std;
const int INF = 99999999;

struct node {
    int to, nxt, w;
}a[1000000] = {0};
struct typekey {
    int x, y;
}keys[12][20] = {0};
int n, M, tot = 0, row, line, keyn;
int layer, r;
int num[12][12], fg[200][200] = {0};
int kn[12] = {0};
int hd[102405] = {0};
bool vis[102405] = {0};
int dis[102405] = {0};
int q[1000000] = {0};

void Read() {
    scanf("%d%d%d%d", &row, &line, &keyn, &r);
    int k = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= line; j++) num[i][j] = ++k;
    }
    int x, y, p;
    for (int i = 1; i <= r; i++) {
        scanf("%d%d", &x, &y);
        int r1 = num[x][y];
        scanf("%d%d", &x, &y);
        int r2 = num[x][y];
        scanf("%d", &p);
        if (p == 0) p = -1;
        fg[r1][r2]= fg[r2][r1] = p;
    }
    scanf("%d", &r);
    for (int i = 1; i <= r; i++) {
        scanf("%d%d%d", &x, &y, &p);
        ++kn[p];
        keys[p][kn[p]].x = x;
        keys[p][kn[p]].y = y;
    }
}

void add(int x, int y, int z) {
    a[++tot].to = y;
    a[tot].w = z;
    a[tot].nxt = hd[x];
    hd[x] = tot;
}

void Build() {
    M = row * line;
    layer = (1 << keyn);
    n = M * layer;
    bool havek[12] = {0};
    for (int i = 0; i < layer; i++) {
        for (int j = 1; j <= keyn; j++) {
            if (i & (1 << (j - 1))) havek[j] = true;
            else havek[j] = false;
        }
        
        for (int j = 1; j <= row; j++) {
            for (int k = 1; k <= line; k++) {
                int x = num[j][k], y = num[j][k + 1];
                if (y != 0 && fg[x][y] != -1) {
                    if (fg[x][y] == 0 || havek[fg[x][y]]) {
                        add(M * i + x, M * i + y, 1);
                        add(M * i + y, M * i + x, 1);
                    }
                }
                y = num[j + 1][k];
                if (y != 0 && fg[x][y] != -1) {
                    if (fg[x][y] == 0 || havek[fg[x][y]]) {
                        add(M * i + x, M * i + y, 1);
                        add(M * i + y, M * i + x, 1);
                    }
                }
            }
        }
        
        for (int j = 1; j <= keyn; j++) {
            if (!havek[j]) {
                int t = i + (1 << (j - 1));
                for (int k = 1; k <= kn[j]; k++) {
                    int x = num[keys[j][k].x][keys[j][k].y];
                    add(M * i + x, M * t + x, 0);
                }
            }
        }
    }
}

void SPFA() {
    int head = 1, tail = 1;
    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[1] = 0, vis[1] = true;
    q[1] = 1;
    while (head <= tail) {
        int u = q[head];
        head++;
        for (int i = hd[u]; i; i = a[i].nxt) {
            int v = a[i].to;
            if (dis[v] > dis[u] + a[i].w) {
                dis[v] = dis[u] + a[i].w;
                if (!vis[v]) {
                    q[++tail] = v;
                    vis[v] = true;
                }
            }
        }
        vis[u] = false;
    }
    
    int T = num[row][line];
    int ans = INF;
    for (int i = 0; i < layer; i++) {
        ans = min(ans, dis[M * i + T]);
    }
    if (ans < INF) printf("%d\n", ans);
    else printf("-1\n");
}

int main() {
    Read();
    Build();
    SPFA();
    
    return 0;
}