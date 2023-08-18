#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 10;
int n, tot;

struct E {
    int u, v;
    int d;
}e[N];

void build_edge(int u, int v, int z) {
    e[++tot].u = u;
    e[tot].v = v;
    e[tot].d = z;
}

int fa[N];
LL sz[N];
LL ans;

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void unionn(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

bool cmp(const E &a, const E &b) {
    return a.d < b.d;
}

int main() {
    cin >> n;
    int x, y, z;
    for (int i = 1; i < n; i++) {
        cin >> x >> y >> z;
        build_edge(x, y, z);
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i, sz[i] = 1;
    }
    sort(e + 1, e + n, cmp);
    
    
    for (int i = 1; i <= tot; i++) {
        int fx = find(e[i].u), fy = find(e[i].v);
        ans += (sz[fx] * sz[fy] - 1) * (e[i].d + 1) + e[i].d;
        unionn(fx, fy);
    }
    
    
    printf("%lld\n", ans);
    

    return 0;
}