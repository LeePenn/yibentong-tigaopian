#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1e6 + 10;
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
int father[N], son[N], dep[N], Size[N], seg[N], top[N], rev[N];
int num[N];
int sum[M], tag[M];
int Sum;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d", &n);
    int v;
    for (int u = 2; u <= n; u++) {
        scanf("%d", &v);
        v++;
        add_edge(u, v); add_edge(v, u);
    }
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
        sum[k] = num[rev[l]];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void update1(int k, int l, int r, int Val) {
    tag[k] = Val;
    sum[k] = (r - l + 1) * Val;
}

void pushDown(int k, int l, int r, int mid) {
    if (tag[k] == -1) return;
    
    update1(k << 1, l, mid, tag[k]);
    update1(k << 1 | 1, mid + 1, r, tag[k]);
    tag[k] = -1;
}

void pushUp(int k) {
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

void update(int k, int l, int r, int li, int ri, int Val) {
    if (l > ri || r < li) return;
    if (l >= li && r <= ri) {
        update1(k, l, r, Val);
        return;
    }
    
    int mid = (l + r) >> 1;
    pushDown(k, l, r, mid);
    if (mid >= li) update(k << 1, l, mid, li, ri, Val);
    if (mid < ri) update(k << 1 | 1, mid + 1, r, li, ri, Val);
    pushUp(k);
}

void ask(int u, int v, int Val) {
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        update(1, 1, seg[0], seg[fu], seg[u], Val);
        u = father[fu];
        fu = top[u];
    }
    
    if (dep[u] > dep[v]) swap(u, v);
    update(1, 1, seg[0], seg[u], seg[v], Val);
}

void calc() {
    scanf("%d", &m);
    char op[12];
    int u;
    string line;
    getline(cin, line);
    
    // Sum = 0;
    // Tot = 0;
    // ask(1, 2);
    // printf("%d %d\n", Sum, Tot);
    // return;
    
    for (int i = 1; i <= m; i++) {
        scanf("%s", op + 1);
        scanf("%d\n", &u);
        u++;
        
        int Sum = sum[1];
        if (op[1] == 'i') {
            ask(1, u, 1);
            printf("%d\n", sum[1] - Sum);
        } else {
            update(1, 1, seg[0], seg[u], seg[u] + Size[u] - 1, 0);
            printf("%d\n", Sum - sum[1]);
        }
    }
}

int main() {
    Read();
    dfs1(1, 0);
    seg[0] = seg[1] = top[1] = rev[1] = 1;
    dfs2(1, 0);
    
    build(1, 1, seg[0]);
    
    memset(tag, -1, sizeof(tag));
    calc();
    
    return 0;
}