#include <bits/stdc++.h>
using namespace std;
struct STU {
    int x, y;
} a[1000005];
int q[100005], son[2000005], num[100005], sta[100005], nxt[2000005], in[100005], head[2000005], f_siz[100005],
    low[100005], dfn[100005], col[100005];
int n, m, ans_max, top, tot, tim, color, i, MOD;
long long f_x[100005], ans_sum;
bool cmp(STU xx, STU yy) {
    return xx.x < yy.x || (xx.x == yy.x && xx.y < yy.y);
}
void add(int x, int y) {
    son[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}
void tarjan(int x) {
    dfn[x] = low[x] = ++tim, sta[++top] = x;

    for (int i = head[x]; i; i = nxt[i])
        if (!dfn[son[i]])
            tarjan(son[i]), low[x] = min(low[x], low[son[i]]);
        else if (!col[son[i]])
            low[x] = min(low[x], dfn[son[i]]);

    if (low[x] == dfn[x]) {
        color++;
        int k = 1;

        while (sta[top] != x)
            col[sta[top--]] = color, k++;

        col[x] = color, top--, num[color] = k;
    }
}
void bfs() {
    int xx, h = 0, t = 0, i;

    for (i = 1; i <= color; i++)
        if (!in[i])
            q[++t] = i, f_x[i] = 1, f_siz[i] = num[i];

    while (h < t)
        for (xx = q[++h], i = head[xx]; i; i = nxt[i]) {
            if (f_siz[son[i]] == f_siz[xx] + num[son[i]])
                f_x[son[i]] = (f_x[son[i]] + f_x[xx]) % MOD;
            else if (f_siz[son[i]] < f_siz[xx] + num[son[i]])
                f_x[son[i]] = f_x[xx] % MOD, f_siz[son[i]] = f_siz[xx] + num[son[i]];

            if (--in[son[i]] == 0)
                q[++t] = son[i];
        }
}
int main() {
    scanf("%d%d%d", &n, &m, &MOD);

    for (i = 1; i <= m; i++)
        scanf("%d%d", &a[i].x, &a[i].y), add(a[i].x, a[i].y);

    for (i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);

    for (i = 1; i <= m; i++)
        a[i].x = col[a[i].x], a[i].y = col[a[i].y];

    memset(head, 0, sizeof(head));
    memset(nxt, 0, sizeof(nxt));
    memset(son, 0, sizeof(son));
    tot = 0, sort(a + 1, a + m + 1, cmp);

    for (i = 1; i <= m; i++)
        if ((a[i].x != a[i - 1].x || a[i].y != a[i - 1].y) && a[i].x != a[i].y)
            add(a[i].x, a[i].y), in[a[i].y]++;

    bfs();

    for (i = 1; i <= color; i++)
        if (f_siz[i] == ans_max)
            ans_sum = (ans_sum + f_x[i]) % MOD;
        else if (f_siz[i] > ans_max)
            ans_max = f_siz[i], ans_sum = f_x[i];

    cout << ans_max << endl << ans_sum << endl;
}