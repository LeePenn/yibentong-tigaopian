#include <bits/stdc++.h>
using namespace std;
const int N = 50, M = 4010;
int s, du[N], tot;
int h[N], cnt, ans[M];
struct cyy {
    int to, ne, w;
    bool f;
} e[M];
void add(int x, int y, int z) {
    e[cnt] = {y, h[x], z, 0};
    h[x] = cnt++;
    du[y]++;
}
void dfs(int x, int p) {
    for (int i = h[x]; ~i; i = e[i].ne) {
        if (e[i].f)
            continue;

        e[i].f = e[i ^ 1].f = 1;
        dfs(e[i].to, e[i].w);
    }

    if (p)
        ans[++tot] = p;
}
void init() {
    memset(du, 0, sizeof(du));
    memset(h, -1, sizeof(h));
    cnt = 0, tot = 0;
}
int main() {
    int x, y, z;

    while (1) {
        scanf("%d%d", &x, &y);

        if (!x && !y)
            return 0;

        init();
        s = min(x, y);
        scanf("%d", &z);
        add(x, y, z);
        add(y, x, z);

        while (~scanf("%d%d", &x, &y)) {
            if (!x && !y)
                break;

            scanf("%d", &z);
            add(x, y, z);
            add(y, x, z);
        }

        bool flag = 0;

        for (int i = 1; i <= 44; i++)
            if (du[i] & 1) {
                puts("Round trip does not exist.");
                flag = 1;
                break;
            }

        if (flag)
            continue;

        dfs(s, 0);

        for (int i = tot; i >= 2; i--)
            printf("%d ", ans[i]);

        printf("%d\n", ans[1]);
    }

    return 0;
}