#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 1e6 + 10;
LL n, m;
struct Edge {
    LL nxt, v;
    Edge() { nxt = v = 0; }
    Edge(LL _nxt, LL _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
LL hd[N], etot;
LL father[N], son[N], dep[N], Size[N], seg[N], top[N], rev[N];
LL num[N], sum[M], add[M], Sum;

void add_edge(LL u, LL v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%lld%lld", &n, &m);
    for (LL i = 1; i <= n; i++) scanf("%lld", &num[i]);
    LL u, v;
    for (LL i = 1; i < n; i++) {
        scanf("%lld%lld", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void dfs1(LL u, LL f) {
    father[u] = f;
    Size[u] = 1;
    dep[u] = dep[f] + 1;
    for (LL i = hd[u]; i; i = edge[i].nxt) {
        LL v = edge[i].v;
        if (v == f) continue;
        dfs1(v, u);
        Size[u] += Size[v];
        if (Size[v] > Size[son[u]]) son[u] = v;
    }
}   

void dfs2(LL u, LL f) {
    if (son[u]) {
        seg[son[u]] = ++seg[0];
        top[son[u]] = top[u];
        rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    
    for (LL i = hd[u]; i; i = edge[i].nxt) {
        LL v = edge[i].v;
        if (!top[v]) {
            seg[v] = ++seg[0];
            top[v] = v;
            rev[seg[0]] = v;
            dfs2(v, u);
        }
    }
}

void pushUp(LL k) {
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void build(LL k, LL l, LL r) {
    if (l == r) {
        sum[k] = num[rev[l]];
        return;
    }
    
    LL mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    pushUp(k);
}

void lan(LL k, LL l, LL r, LL Val) {
    add[k] += (LL)Val;
    sum[k] += (LL)(r - l + 1) * Val;
}

void pushDown(LL k, LL l, LL r, LL mid) {
    if (add[k] == 0) return;
    
    lan(k << 1, l, mid, add[k]);
    lan(k << 1 | 1, mid + 1, r, add[k]);
    add[k] = 0;
}

void update(LL k, LL l, LL r, LL li, LL ri, LL Val) {
    if (l >= li && r <= ri) {
        lan(k, l, r, Val);
        return;
    }
    
    LL mid = (l + r) >> 1;
    pushDown(k, l, r, mid);
    if (mid >= li) update(k << 1, l, mid, li, ri, Val);
    if (mid < ri) update(k << 1 | 1, mid + 1, r, li, ri, Val);
    pushUp(k);
}

void update1(LL x, LL Val) {
    update(1, 1, seg[0], seg[x], seg[x] + Size[x] - 1, Val);
}

void query(LL k, LL l, LL r, LL li, LL ri) {
    if (l >= li && r <= ri) {
        Sum += sum[k];
        return;
    }
    
    LL mid = (l + r) >> 1;
    pushDown(k, l, r, mid);
    if (mid >= li) query(k << 1, l, mid, li, ri);
    if (mid < ri) query(k << 1 | 1, mid + 1, r, li, ri);
}

void ask(LL u, LL v) {
    LL fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv), swap(u, v);
        }
        
        query(1, 1, seg[0], seg[fu], seg[u]);
        u = father[fu];
        fu = top[u];
    }
    
    if (dep[u] > dep[v]) swap(u, v);
    query(1, 1, seg[0], seg[u], seg[v]);
}

void calc() {
    LL op, x, a;
    for (LL i = 1; i <= m; i++) {
        scanf("%lld", &op);
        if (op == 1) {
            scanf("%lld%lld", &x, &a);
            update(1, 1, seg[0], seg[x], seg[x], a);
        } else if (op == 2) {
            scanf("%lld%lld", &x, &a);
            update1(x, a);
        } else {
            scanf("%lld", &x);
            Sum = 0;
            ask(1, x);
            printf("%lld\n", Sum);
        }
    }
}

int main() {
    Read();
    
    dfs1(1, 0);
    seg[0] = seg[1] = top[1] = rev[1] = 1;
    dfs2(1, 0);
    
    build(1, 1, seg[0]);
    
    calc();

    return 0;
}