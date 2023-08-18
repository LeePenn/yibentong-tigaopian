#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10, M = 1e6 + 10;
int n, m;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int num[N];
int father[N], son[N], dep[N], Size[N], seg[N], rev[N], top[N];
int sum[M], Max[M];
int Sum, Maxx;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
    
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
}

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    Size[u] = 1;
    father[u] = f;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f) continue;
        dfs1(v, u);
        Size[u] += Size[v];
        if (Size[v] > Size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int f) {
    if (son[u]) {
        seg[son[u]] = ++seg[0];
        top[son[u]] = top[u];
        rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!top[v]) {
            seg[v] = ++seg[0];
            top[v] = v;
            rev[seg[0]] = v;
            dfs2(v, u);
        }
    }
}

void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = Max[k] = num[rev[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
    Max[k] = max(Max[k << 1], Max[k << 1 | 1]);
}

void update(int k, int l, int r, int pos, int Val) {
    if (pos > r || pos < l) return;
    if (l == r && l == pos) {
        sum[k] = Max[k] = Val;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= pos) update(k << 1, l, mid, pos, Val);
    else update(k << 1 | 1, mid + 1, r, pos, Val);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
    Max[k] = max(Max[k << 1], Max[k << 1 | 1]);
}

void query(int k, int l, int r, int li, int ri) {
    if (li > r || ri < l) return;
    if (l >= li && r <= ri) {
        Sum += sum[k];
        Maxx = max(Maxx, Max[k]);
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= li) query(k << 1, l, mid, li, ri);
    if (mid < ri) query(k << 1 | 1, mid + 1, r, li, ri);
}

void ask(int u, int v) {
    int fu = top[u], fv = top[v];
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
    scanf("%d", &m);
    char sr[10];
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%s", sr + 1);
        scanf("%d%d", &u, &v);
        if (sr[1] == 'C') {
            update(1, 1, seg[0], seg[u], v);
        } else {
            Sum = 0, Maxx = -10000000;
            ask(u, v);
            if (sr[2] == 'M') printf("%d\n", Maxx);
            else printf("%d\n", Sum);
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
