#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 3000 + 4, M = 1e4 + 4;
const double INF = 1e11, EPS = 1e-9;
int n, m;
struct Edge {
    int v, nxt;
    double w;
}edge[M];
int hd[N], tot;
bool FC;
double dist[N];
int vis[N];

void add_edge(int u, int v, double w) {
    edge[++tot].nxt = hd[u];
    edge[tot].v = v;
    edge[tot].w = w;
    hd[u] = tot;
}

void SPFA(int u, int root, double mid) {
    if (FC) return;
    vis[u] = root;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (dist[u] + edge[i].w - mid < dist[v]) {
            dist[v] = dist[u] + edge[i].w - mid;
            if (!vis[v]) SPFA(v, root, mid);
            if (FC) return;
            else if (vis[v] == root) {
                FC = true;
                return;
            }
        }
    }
    vis[u] = 0;
}

bool check(double mid) {
    FC = false;
    for (int i = 1; i <= n; i++) {
        dist[i] = 0;
        vis[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        SPFA(i, i, mid);
        if (FC) break;
    }
    return FC;

}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    double l = -INF, r = INF;
    
    while (l + EPS < r) {
        double mid = (l + r) / 2;
        // printf("%lf\n", mid);
        if (check(mid)) {
            r = mid;
        } else l = mid;
    }
    
    printf("%.8lf\n", l);

    return 0;
}