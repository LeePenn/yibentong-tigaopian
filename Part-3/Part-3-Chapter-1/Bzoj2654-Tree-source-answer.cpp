#include <bits/stdc++.h>
using namespace std;
int f[200005], n, m, need, tot, sum, cnt, ans;
struct mst {
    int u, v, w, c, W;
    bool operator<(const mst &a)const {
        return W == a.W ? c < a.c : W < a.W;
    }
} e[200005];
int find(int x) {
    return f[x] = f[x] == x ? x : find(f[x]);
}
bool check(int mid) {
    cnt = sum = tot = 0;

    for (int i = 1; i <= m; i++) {
        if (!e[i].c)
            e[i].W = e[i].w + mid;
        else
            e[i].W = e[i].w;
    }

    sort(e + 1, e + m + 1);

    for (int i = 1; i <= n; ++i)
        f[i] = i;

    for (int i = 1; i <= m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);

        if (u != v) {
            f[u] = v;
            sum += e[i].W;
            tot++;

            if (!e[i].c)
                ++cnt;
        }

        if (tot == n - 1)
            break;
    }

    return cnt >= need;
}
int main() {
    int l = -1e5, r = 1e5;
    scanf("%d%d%d", &n, &m, &need);

    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].c);
        e[i].u++;
        e[i].v++;
    }

    while (l <= r) {
        int mid = (l + r) >> 1;

        if (check(mid))
            l = mid + 1, ans = sum - need * mid;
        else
            r = mid - 1;
    }

    printf("%d", ans);
    return 0;
}