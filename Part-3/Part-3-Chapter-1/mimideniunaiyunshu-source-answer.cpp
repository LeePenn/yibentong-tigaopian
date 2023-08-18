#include <bits/stdc++.h>
using namespace std;
const int N = 510, M = 1e4 + 6;
typedef long long LL;
int e[N * 2], w[N * 2], ne[N * 2], h[N], idx;
int dist[N][N];
int p[N];
LL sum = 0, res = 1e18;
struct edge {
    int a, b;
    int w;
    bool operator<(const edge &a) const {
        return w < a.w;
    }
} ed[M];
int n, m;
int find(int x) {
    if (p[x] != x)
        p[x] = find(p[x]);

    return p[x];
}
void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
void dfs(int u, int fa, int v, int d[]) {
    d[u] = v;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];

        if (j != fa) {
            dfs(j, u, max(v, w[i]), d);
        }
    }
}
int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i++)
        p[i] = i;

    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &ed[i].a, &ed[i].b, &ed[i].w);

    sort(ed, ed + m);

    for (int i = 0; i < m; i++) {
        int a = find(ed[i].a), b = find(ed[i].b), w = ed[i].w;

        if (a != b) {
            p[a] = b;
            sum += w;
            add(a, b, w);
            add(b, a, w);
        }
    }

    for (int i = 1; i <= n; i++)
        dfs(i, -1, 0, dist[i]);

    for (int i = 0; i < m; i++) {
        int a = ed[i].a, b = ed[i].b, w = ed[i].w;

        if (w > dist[a][b]) {
            res = min(sum + w - dist[a][b], res);
        }
    }

    printf("%lld", res);
    return 0;
}