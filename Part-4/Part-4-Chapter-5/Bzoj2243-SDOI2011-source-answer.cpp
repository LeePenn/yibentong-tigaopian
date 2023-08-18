#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, INF = 2139062143;
int n, m, u, v, a, b, c;
char opt;
int w[N], wt[N], siz[N], fa[N], top[N], son[N], id[N], dep[N], cnt;
int head[N], to[N << 1], nxt[N << 1], tot;
int sum[N << 2], lc[N << 2], rc[N << 2], laz[N << 2];
int nlc, nrc, pos1, pos2;
int read() {
    int r = 0, f = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        r = (r << 1) + (r << 3) + c - 48;
        c = getchar();
    }

    return r * f;
}
void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
int ls(int x) {
    return x << 1;
}
int rs(int x) {
    return x << 1 | 1;
}
void push_up(int x) {
    sum[x] = sum[ls(x)] + sum[rs(x)];

    if (rc[ls(x)] == lc[rs(x)])
        sum[x]--;

    lc[x] = lc[ls(x)];
    rc[x] = rc[rs(x)];
}
void build(int p, int l, int r) {
    if (l == r) {
        sum[p] = 1;
        lc[p] = wt[l];
        rc[p] = wt[l];
        return ;
    }

    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}
void push_down(int x) {
    laz[ls(x)] = laz[x];
    laz[rs(x)] = laz[x];
    sum[ls(x)] = sum[rs(x)] = 1;
    lc[ls(x)] = rc[ls(x)] = laz[x];
    lc[rs(x)] = rc[rs(x)] = laz[x];
    laz[x] = INF;
}
void update(int p, int l, int r, int L, int R, int k) {
    if (L <= l && r <= R) {
        sum[p] = 1;
        lc[p] = rc[p] = k;
        laz[p] = k;
        return ;
    }

    if (laz[p] != INF)
        push_down(p);

    int mid = (l + r) >> 1;

    if (L <= mid)
        update(ls(p), l, mid, L, R, k);

    if (R > mid)
        update(rs(p), mid + 1, r, L, R, k);

    push_up(p);
}
void dfs1(int f, int now, int deep) {
    fa[now] = f;
    dep[now] = deep;
    siz[now] = 1;
    int hson = -1;

    for (int i = head[now]; i; i = nxt[i]) {
        int v = to[i];

        if (v == f)
            continue;

        dfs1(now, v, deep + 1);
        siz[now] += siz[v];

        if (siz[v] > hson) {
            hson = siz[v];
            son[now] = v;
        }
    }
}
void dfs2(int now, int topf) {
    id[now] = ++cnt;
    wt[cnt] = w[now];
    top[now] = topf;

    if (son[now] == 0)
        return ;

    dfs2(son[now], topf);

    for (int i = head[now]; i; i = nxt[i]) {
        int v = to[i];

        if (v == fa[now] || v == son[now])
            continue;

        dfs2(v, v);
    }
}
int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        if (L == l)
            nlc = lc[p];

        if (r == R)
            nrc = rc[p];

        return sum[p];
    }

    if (laz[p] != INF)
        push_down(p);

    int mid = (l + r) >> 1, lsr = 0, rsr = 0, res = 0;

    if (L <= mid)
        lsr = query(ls(p), l, mid, L, R);

    if (R > mid)
        rsr = query(rs(p), mid + 1, r, L, R);

    res = lsr + rsr;

    if (lsr == 0 || rsr == 0)
        return res;
    else if (rc[ls(p)] == lc[rs(p)])
        res--;

    return res;
}
void updrange(int x, int y, int k) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);

        update(1, 1, n, id[top[x]], id[x], k);
        x = fa[top[x]];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    update(1, 1, n, id[x], id[y], k);
}
int qrange(int x, int y) {
    int ans = 0;
    pos1 = pos2 = INF;

    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y), swap(pos1, pos2);

        ans += query(1, 1, n, id[top[x]], id[x]);

        if (nrc == pos1)
            ans--;

        x = fa[top[x]];
        pos1 = nlc;
    }

    if (dep[x] > dep[y])
        swap(x, y), swap(pos1, pos2);

    ans += query(1, 1, n, id[x], id[y]);

    if (nlc == pos1)
        ans--;

    if (nrc == pos2)
        ans--;

    return ans;
}
int main() {
    memset(laz, 0x7f, sizeof laz);
    n = read();
    m = read();

    for (int i = 1; i <= n; i++)
        w[i] = read();

    for (int i = 1; i < n; i++) {
        u = read();
        v = read();
        add(u, v);
        add(v, u);
    }

    dfs1(0, 1, 0);
    dfs2(1, 1);
    build(1, 1, n);

    while (m--) {
        cin >> opt;

        if (opt == 'C') {
            a = read();
            b = read();
            c = read();
            updrange(a, b, c);
        }

        if (opt == 'Q') {
            a = read();
            b = read();
            printf("%d\n", qrange(a, b));
        }
    }

    return 0;
}