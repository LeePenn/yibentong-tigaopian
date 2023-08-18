#include <bits/stdc++.h>
using namespace std;
int n, m, e[30005], ne[30005], h[10005], idx;
int dfn[10005], low[10005], cnt, ans, rt;
inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void tan(int u) {
    dfn[u] = low[u] = ++cnt;
    int num = 0;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];

        if (!dfn[j]) {
            tan(j);
            low[u] = min(low[u], low[j]);

            if (low[j] >= dfn[u])
                num++;
        } else
            low[u] = min(low[u], dfn[j]);
    }

    if (u != rt)
        num++;

    ans = max(ans, num);
}
int main() {
    while (cin >> n >> m && n) {
        ans = idx = cnt = 0;
        memset(h, -1, sizeof(h));
        memset(dfn, 0, sizeof(dfn));
        int a, b, num = 0;

        while (m--) {
            scanf("%d%d", &a, &b);
            add(a, b);
            add(b, a);
        }

        for (rt = 0; rt < n; rt++)
            if (!dfn[rt])
                num++, tan(rt);

        cout << ans + num - 1 << endl;
    }

    return 0;
}