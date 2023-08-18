#include <bits/stdc++.h>
using namespace std;
long long n, m, head[1000100], e, tree[1000100], rnk[1000100], add[1000100], b[1000100], id[1000100],
     siz[1000100];
long long dep[1000100], top[1000100], tot, fa[1000100], son[1000100];
struct o {
    long long ne, to;
} a[1000100];
void dd(long long u, long long v) {
    a[++e].ne = head[u];
    a[e].to = v;
    head[u] = e;
}
long long ls(long long x) {
    return x << 1;
}
long long rs(long long x) {
    return x << 1 | 1;
}
void pup(long long k) {
    tree[k] = tree[ls(k)] + tree[rs(k)];
}
void build(long long k, long long l, long long r) {
    if (l == r) {
        tree[k] = b[rnk[l]];
        return;
    }

    long long mid = (l + r) >> 1;
    build(ls(k), l, mid);
    build(rs(k), mid + 1, r);
    pup(k);
}
void lan(long long k, long long l, long long r, long long v) {
    add[k] += v;
    tree[k] += (r - l + 1) * v;
}
void pud(long long k, long long l, long long r, long long mid) {
    if (!add[k])
        return;

    lan(ls(k), l, mid, add[k]);
    lan(rs(k), mid + 1, r, add[k]);
    add[k] = 0;
}
void change(long long k, long long l, long long r, long long x, long long y, long long v) {
    if (x <= l && y >= r) {
        lan(k, l, r, v);
        return;
    }

    long long mid = (l + r) >> 1;
    pud(k, l, r, mid);

    if (x <= mid)
        change(ls(k), l, mid, x, y, v);

    if (y > mid)
        change(rs(k), mid + 1, r, x, y, v);

    pup(k);
}
long long ask(long long k, long long l, long long r, long long x, long long y) {
    if (x <= l && y >= r) {
        return tree[k];
    }

    long long mid = (l + r) >> 1, res = 0;
    pud(k, l, r, mid);

    if (x <= mid)
        res += ask(ls(k), l, mid, x, y);

    if (y > mid)
        res += ask(rs(k), mid + 1, r, x, y);

    return res;
}
void change1(long long x, long long v) {
    change(1, 1, n, id[x], id[x] + siz[x] - 1, v);
}
long long ask1(long long x, long long y) {
    long long res = 0;

    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);

        res += ask(1, 1, n, id[top[x]], id[x]);
        x = fa[top[x]];
    }

    if (dep[x] > dep[y])
        swap(x, y);

    res += ask(1, 1, n, id[x], id[y]);
    return res;
}
void dfs1(int x, int f) {
    dep[x] = dep[f] + 1;
    fa[x] = f;
    siz[x] = 1;

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
void dfs2(long long x, long long tp) {
    id[x] = ++tot;
    rnk[tot] = x;
    top[x] = tp;

    if (!son[x])
        return;

    dfs2(son[x], tp);

    for (long long i = head[x]; i; i = a[i].ne) {
        long long v = a[i].to;

        if (v != fa[x] && v != son[x])
            dfs2(v, v);

        //continue;
    }
}
long long read() {
    long long x = 0, f = 1;
    char ch = getchar();

    while (ch > '9' || ch < '0') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }

    return x * f;
}
int main() {
    //  n=read();m=read();cout<<n<<m<<endl;
    scanf("%lld%lld", &n, &m);

    for (long long i = 1; i <= n; i++)
        scanf("%lld", &b[i]); //b[i]=read();

    for (long long i = 1; i < n; i++) {
        long long u, v;
        scanf("%lld%lld", &u, &v);

        //      long long u=read(),v=read();
        if (u == v)
            continue;

        dd(u, v);
        dd(v, u);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);

    while (m--) {
        long long op;
        scanf("%lld", &op);
        long long x, v;

        if (op == 1) {
            scanf("%lld%lld", &x, &v);
            //          long long x=read(),v=read();
            change(1, 1, n, id[x], id[x], v);
        } else if (op == 2) {
            //          long long x=read(),v=read();
            scanf("%lld%lld", &x, &v);
            change1(x, v);
        } else {
            scanf("%lld", &x);
            //          long long x=read();
            printf("%lld\n", ask1(1, x));
        }
    }

    return 0;
}