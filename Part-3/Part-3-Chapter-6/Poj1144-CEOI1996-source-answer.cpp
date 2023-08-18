#include <bits/stdc++.h>
using namespace std;
int n, h[1005], tot, dfn[1005], low[1005], num, a, flag[1005];
char k;
struct kkk {
    int to, ne;
} e[1005];
inline void add(int x, int y) {
    e[++tot].to = y;
    e[tot].ne = h[x];
    h[x] = tot;
}
inline void tarjan(int x) {
    int tot = 0;
    dfn[x] = low[x] = ++num;

    for (int i = h[x]; i; i = e[i].ne) {
        int u = e[i].to;

        if (!dfn[u]) {
            tarjan(u);
            low[x] = min(low[x], low[u]);

            if (low[u] >= dfn[x]) {
                tot++;

                if (x != 1 || tot > 1)
                    flag[x] = true;
            }
        } else
            low[x] = min(low[x], dfn[u]);
    }
}

inline void init() {
    memset(h, 0, sizeof(h));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(flag, 0, sizeof(flag));
    tot = num = 0;
}
int main() {
    int a, b;
    char k;

    while (scanf("%d", &n) == 1 && n) {
        init();

        while (scanf("%d", &a) == 1 && a) {
            while ((k = getchar()) != '\n') {
                scanf("%d", &b);
                add(a, b);
                add(b, a);
            }
        }

        int ans = 0;

        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);

        for (int i = 1; i <= n; i++)
            if (flag[i])
                ans++;

        printf("%d\n", ans);
    }

    return 0;
}