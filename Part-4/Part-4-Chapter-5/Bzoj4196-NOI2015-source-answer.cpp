#include <bits/stdc++.h>
using namespace std;
int n, d, e, head[1000100], siz[1000100], tot, fa[1000100], dep[1000100], son[1000100], top[1000100];
int id[1000100], rnk[1000100], tree[1000100], add[1000100], m;
struct o {
    int ne, to;
} a[1000100];
int ls(int k) {
    return k << 1;
}
int rs(int k) {
    return k << 1 | 1;
}
void dd(int u, int v) {
    a[++e].ne = head[u];
    a[e].to = v;
    head[u] = e;
}
void dfs1(int x, int f) {
    siz[x] = 1;
    dep[x] = dep[f] + 1;
    fa[x] = f;

    for (int i = head[x]; i; i = a[i].ne) {
        int v = a[i].to;

        if (v == f)
            continue;

        dfs1(v, x);
        siz[x] += siz[v];

        if (siz[v] > siz[son[x]] || !son[x])
            son[x] = v;
    }
}
void dfs2(int x, int tp) {
    top[x] = tp;
    id[x] = ++tot;
    rnk[tot] = x;

    if (!son[x])
        return;

    dfs2(son[x], tp);

    for (int i = head[x]; i; i = a[i].ne) {
        int v = a[i].to;

        if (v == fa[x] || v == son[x])
            continue;

        dfs2(v, v);
    }
}
void pup(int k) {
    tree[k] = tree[ls(k)] + tree[rs(k)];
}
void lan(int k, int l, int r, int v) {
    add[k] = v;
    tree[k] = (r - l + 1) * v;
}
void pud(int k, int l, int r, int mid) {
    if (add[k] == -1)
        return;

    lan(ls(k), l, mid, add[k]);
    lan(rs(k), mid + 1, r, add[k]);
    add[k] = -1;
}
void change(int k, int l, int r, int x, int y, int v) {
    if (x <= l && y >= r) {
        lan(k, l, r, v);
        return;
    }

    int mid = (l + r) >> 1;
    pud(k, l, r, mid);

    if (x <= mid)
        change(ls(k), l, mid, x, y, v);

    if (y > mid)
        change(rs(k), mid + 1, r, x, y, v);

    pup(k);
}
void change1(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);

        change(1, 1, n, id[top[x]], id[x], z);
        x = fa[top[x]];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    change(1, 1, n, id[x], id[y], z);
}
void build(int k, int l, int r) {
    if (l == r) {
        add[k] = -1;
        return;
    }

    int mid = (l + r) >> 1;
    build(ls(k), l, mid);
    build(rs(k), mid + 1, r);
    pup(k);
}
int read() {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch > '9' || ch < '0') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch <= '9' && ch >= '0') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }

    return x * f;
}
int main() {
    n = read();

    //  memset(add,01,sizeof(add));
    for (int i = 2; i <= n; i++) {
        int x = read();
        dd(x + 1, i);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    m = read();

    while (m--) {
        char op[10];
        scanf("%s", &op);
        int x = read();
        int h1 = tree[1];

        if (op[0] == 'i') {
            change1(1, x + 1, 1);
            printf("%d\n", tree[1] - h1);
        } else {
            change(1, 1, n, id[x + 1], id[x + 1] + siz[x + 1] - 1, 0);
            printf("%d\n", h1 - tree[1]);
        }
    }

    return 0;
}