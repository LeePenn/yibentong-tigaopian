#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, M = 1e5 + 10;
struct E {
    int u, v, w, ww, col;
    bool operator < (const E &rh) const {
        return ww == rh.ww ? col < rh.col : ww < rh.ww;
    }
}e[M];
int fa[N];
int n, m, k;
int sum;

int find(int u) {
    if (fa[u] != u) fa[u] = find(fa[u]);
    return fa[u];
}

void unionn(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) {
        fa[v] = u;
    }
}

bool check(int mid) {
    for (int i = 1; i <= m; i++) {
        if (!e[i].col) {
            e[i].ww = e[i].w + mid;
        } else e[i].ww = e[i].w;
    }
    for (int i = 1; i <= n; i++) fa[i] = i;
    
    sort(e + 1, e + m + 1);
    sum = 0;
    int cnt = 0;
    int white = 0;
    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u != v) {
            sum += e[i].ww;
            unionn(u, v);
            cnt++;
            if (!e[i].col) white++;
        }
        if (cnt == n - 1) break;
    }
    
    return white >= k;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d %d", &e[i].u, &e[i].v, &e[i].w, &e[i].col);
        e[i].u++, e[i].v++;
    }
    int l = -100, r = 100;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = sum - mid * k;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}