#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int ver[N << 1], nxt[N << 1], head[N], tot;
int n, f[N], g[N], ans, p;
bool yes[N];
void add(int x, int y) {
    ver[++ tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}
int dfs(int x, int fa) {
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];

        if (y == fa)
            continue;

        int res = dfs(y, x) + 1;

        if (res > f[x])
            g[x] = f[x], f[x] = res;
        else if (res > g[x])
            g[x] = res;
    }

    ans = max(ans, f[x] + g[x]);
    return f[x];
}
void find(int x, int fa, int len) {
    yes[x] = 1;

    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];

        if (y == fa)
            continue;

        if (f[y] + 1 == len)
            find(y, x, f[y]);
    }
}
int main() {
    scanf("%d", &n);

    for (int i = 1, x, y; i < n; i ++) {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }

    dfs(0, -1);

    for (int i = 0; i < n; i ++)
        if (f[i] + g[i] == ans) {
            p = i;
            find(p, -1, f[p]);
            find(p, -1, g[p]);
        }

    for (int i = 0; i < n; i ++)
        if (yes[i])
            printf("%d\n", i);

    return 0;
}