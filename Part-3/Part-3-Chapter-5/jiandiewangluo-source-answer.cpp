#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int n, p, m, top, tot, i, j, x, y, ans, to[N * 3], nxt[N * 3], head[N], co[N], col, num, dfn[N], low[N],
    si[N], st[N], rd[N], sum[N], a[N];
void add(int x, int y) {
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}
void Tarjan(int u) {
    dfn[u] = low[u] = ++num;
    st[++top] = u;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];

        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!co[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        ++col;

        while (st[top + 1] != u) {
            co[st[top]] = col;
            ++si[col];
            sum[col] = min(sum[col], a[st[top]]);
            --top;
        }
    }
}
int main() {
    memset(a, 0x3f, sizeof(a));
    memset(sum, 0x3f, sizeof(sum));
    scanf("%d%d", &n, &p);

    for (i = 1; i <= p; i++)
        scanf("%d", &x), scanf("%d", &a[x]);

    scanf("%d", &m);

    for (i = 1; i <= m; i++)
        scanf("%d%d", &x, &y), add(x, y);

    for (i = 1; i <= n; i++)
        if (!dfn[i] && a[i] <= 20000)
            Tarjan(i);

    for (i = 1; i <= n; i++)
        if (!dfn[i]) {
            printf("NO\n%d", i);
            return 0;
        }

    for (i = 1; i <= n; i++)
        for (j = head[i]; j; j = nxt[j])
            if (co[i] != co[to[j]])
                rd[co[to[j]]]++;

    for (i = 1; i <= col; i++)
        if (!rd[i])
            ans += sum[i];

    printf("YES\n%d", ans);
    return 0;
}