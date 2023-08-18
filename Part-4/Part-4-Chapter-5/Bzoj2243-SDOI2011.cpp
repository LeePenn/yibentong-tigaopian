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
// 端点颜色
int sum[M], lc[M], rc[M], lazy[M];
// 因为是树链剖分，所以树上连续的段其实线段树中未必连续，需要记录算完一段的始末端点颜色
int nlc, nrc;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

void Read() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
    
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void dfs1(int u, int f) {
    father[u] = f;
    dep[u] = dep[f] + 1;
    Size[u] = 1;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == f) continue;
        dfs1(v, u);
        Size[u] += Size[v];
        if (Size[v] > Size[son[u]]) son[u] = v;
    }
}

void dfs2(int u) {
    if (son[u]) {
        seg[son[u]] = ++seg[0];
        top[son[u]] = top[u];
        rev[seg[0]] = son[u];
        dfs2(son[u]);
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!top[v]) {
            seg[v] = ++seg[0];
            top[v] = v;
            rev[seg[0]] = v;
            dfs2(v);
        }
    }
}

void pushUp(int k) {
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
    if (rc[k << 1] == lc[k << 1 | 1]) {
        sum[k]--;
    }
    
    lc[k] = lc[k << 1];
    rc[k] = rc[k << 1 | 1];
}

void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = 1;
        lc[k] = rc[k] = num[rev[l]];
        return;
    }
    
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    pushUp(k);
}

void update1(int k, int col) {
    sum[k] = 1;
    lc[k] = rc[k] = col;
    lazy[k] = col;
}

void pushDown(int k) {
    if (lazy[k] == -1) return;
    
    update1(k << 1, lazy[k]);
    update1(k << 1 | 1, lazy[k]);
    lazy[k] = -1;
}

void update(int k, int l, int r, int li, int ri, int col) {
    if (l > ri || r < li) return;
    if (l >= li && r <= ri) {
        update1(k, col);
        return;
    }
    
    int mid = (l + r) >> 1;
    pushDown(k);
    if (mid >= li) update(k << 1, l, mid, li, ri, col);
    if (mid < ri) update(k << 1 | 1, mid + 1, r, li, ri, col);
    pushUp(k);
}

void updateRange(int u, int v, int col) {
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        update(1, 1, seg[0], seg[fu], seg[u], col);
        u = father[fu];
        fu = top[u];
    }
    
    if (dep[u] > dep[v]) swap(u, v);
    update(1, 1, seg[0], seg[u], seg[v], col);
}

int query(int k, int l, int r, int li, int ri) {
    if (l > ri || r < li) return 0;
    if (l >= li && r <= ri) {
        if (li == l) nlc = lc[k];
        if (ri == r) nrc = rc[k];
        return sum[k];
    }
    
    int mid = (l + r) >> 1;
    // 别忘了pushDown，因为子节点需要query
    pushDown(k);
    
    int lsr = 0, rsr = 0;
    if (mid >= li) lsr = query(k << 1, l, mid, li, ri);
    if (mid < ri) rsr = query(k << 1 | 1, mid + 1, r, li, ri);
    
    int ans = lsr + rsr;
    if (lsr == 0 || rsr == 0) return ans;
    else if (lc[k << 1 | 1] == rc[k << 1]) return ans - 1;
    return ans;
}

int queryRange(int u, int v) {
    int ans = 0;
    int fu = top[u], fv = top[v];
    
    int pos1 = -1, pos2 = -1;
    // 查询顺序是从树下到树上
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
            swap(pos1, pos2);
        }
        ans += query(1, 1, seg[0], seg[fu], seg[u]);
        if (nrc == pos1) ans--;
        
        u = father[fu];
        fu = top[u];
        pos1 = nlc;
    }
    
    if (dep[u] > dep[v]) {
        swap(u, v);
        swap(pos1, pos2);
    }
    ans += query(1, 1, seg[0], seg[u], seg[v]);
    if (nlc == pos1) ans--;
    if (nrc == pos2) ans--;
    
    return ans;
}

void calc() {
    string line;
    char op;
    int a, b, c;
    getline(cin, line);
    for (int i = 1; i <= m; i++) {
        op = getchar();
        if (op == 'C') {
            scanf("%d%d%d\n", &a, &b, &c);
            updateRange(a, b, c);
        } else if (op == 'Q') {
            scanf("%d%d\n", &a, &b);
            printf("%d\n", queryRange(a, b));
        }
    }
}

int main() {
    Read();
    dfs1(1, 0);
    seg[0] = seg[1] = top[1] = rev[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    memset(lazy, -1, sizeof(lazy));
    
    calc();

    return 0;
}