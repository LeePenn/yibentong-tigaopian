#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 300 + 10, INF = 0x7fffffff >> 1;
int n, v[N], g[N][N];
struct E {
    int u, v;
    int c;
}e[N * N * 2];
int tot;
int fa[N * 2];
LL ans;

void init() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            g[i][j] = g[j][i] = INF;
        }
    }
    for (int i = 0; i <= n; i++) g[i][i] = 0;
}

void build_edge(int a, int b, int c) {
    e[++tot].u = a;
    e[tot].v = b;
    e[tot].c = c;
}

bool cmp(const E &a, const E &b) {
    return a.c < b.c;
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void kruskal() {
    for (int i = 1; i <= tot; i++) {
        int u = e[i].u, v = e[i].v, c = e[i].c;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            ans += c;
            fa[fv] = fu;
        }
    }    
    printf("%lld\n", ans);
}

int main() {
    cin >> n;
    init();
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i <= 2 * n; i++) {
        fa[i] = i;
    }
    
    int x;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> x;
            build_edge(i, j, x), build_edge(j, i, x);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        build_edge(0, i, v[i]), build_edge(i, 0, v[i]);
    }
    sort(e + 1, e + tot + 1, cmp);
    
    kruskal();
    

    return 0;
}