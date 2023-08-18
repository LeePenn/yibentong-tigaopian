#include <bits/stdc++.h>
using namespace std;
inline int rd(void) {
    int s = 0, f = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = 0;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        s = s * 10 + c - 48;
        c = getchar();
    }

    return f ? s : -s;
}
const int N = 1e5 + 1e3 + 10;
int n, m, cnt;
int fa[N], deg[N], ans[N], num[N], flag[N];
int findf(int u) {
    return fa[u] == u ? u : fa[u] = findf(fa[u]);
}
signed main() {
    n = rd(), m = rd();

    for (int i = 1; i < N; i++)
        fa[i] = i;

    for (int i = 1, u, v; i <= m; i++) {
        u = rd(), v = rd();

        if (!u)
            u = ++n;

        if (!v)
            v = ++n;

        deg[u]++, deg[v]++;
        fa[findf(u)] = findf(v);
    }

    for (int i = 1; i <= n; i++)
        if (deg[i] && findf(i) == i)
            cnt++;

    if (cnt == 1) {
        int Ans = 0, Num = 0;

        for (int i = 1; i <= n; i++) {
            if (deg[i] > 2)
                Ans++;

            if (deg[i] & 1)
                Num++;
        }

        printf("%d\n", Ans + Num / 2);
    } else {
        int sum = 0;

        for (int i = 1; i <= n; i++) {
            if (deg[i] > 2)
                ans[findf(i)]++, flag[findf(i)] = 1;

            if (deg[i] & 1)
                num[findf(i)]++;
        }

        for (int i = 1; i <= n; i++) {
            if (deg[i] && findf(i) == i) {
                if (num[i])
                    sum += ans[i] + num[i] / 2 - 1;
                else
                    sum += ans[i] + (!flag[i]);
            }
        }

        printf("%d\n", sum + cnt);
    }

    return 0;
}