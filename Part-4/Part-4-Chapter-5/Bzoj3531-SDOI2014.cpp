#include <bits/stdc++.h>
using namespace std;
// 动态开点，root有很多个，可能超过1e6
const int N = 1e5 + 10, M = 2e6 + 10;
int n, m;
int w[N], c[N];
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int father[N], son[N], Size[N], dep[N], seg[N], top[N], revw[N], revc[N];
int root[M];
int ls[M], rs[M], sum[M], maxx[M], roottot;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
} 

void Read() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &c[i]);
    }
    
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
}

void dfs1(int u, int f) {
    father[u] = f;
    Size[u] = 1;
    dep[u] = dep[f] + 1;
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
        revw[seg[0]] = w[son[u]];
        revc[seg[0]] = c[son[u]];
        dfs2(son[u]);
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!top[v]) {
            seg[v] = ++seg[0];
            top[v] = v;
            revw[seg[0]] = w[v];
            revc[seg[0]] = c[v];
            dfs2(v);
        }
    }
}

void pushUp(int k) {
    sum[k] = sum[ls[k]] + sum[rs[k]];
    maxx[k] = max(maxx[ls[k]], maxx[rs[k]]);
}

void update1(int &k, int l, int r, int x, int Val) {
    if (!k) {
        k = ++roottot;
    }
    
    if (l == r) {
        sum[k] = maxx[k] = Val;
        return;
    }
    
    int mid = (l + r) >> 1;
    if (mid >= x) update1(ls[k], l, mid, x, Val);
    if (mid < x) update1(rs[k], mid + 1, r, x, Val);
    pushUp(k);
}

void updateCC(int x, int c) {
    // current religion
    int cc = revc[seg[x]];
    revc[seg[x]] = c;
    update1(root[cc], 1, seg[0], seg[x], 0);
    update1(root[c], 1, seg[0], seg[x], revw[seg[x]]);
}

void updateCW(int x, int w) {
    int cc = revc[seg[x]];
    revw[seg[x]] = w;
    update1(root[cc], 1, seg[0], seg[x], w);
}

int queryQS(int k, int l, int r, int li, int ri) {
    if (!k) return 0;
    
    if (l > ri || r < li) return 0;
    if (l >= li && r <= ri) {
        return sum[k];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (mid >= li) ans += queryQS(ls[k], l, mid, li, ri);
    if (mid < ri) ans += queryQS(rs[k], mid + 1, r, li, ri);
    return ans;
}

int QS(int u, int v) {
    int ans = 0, cc = revc[seg[u]];
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        ans += queryQS(root[cc], 1, seg[0], seg[fu], seg[u]);
        u = father[fu];
        fu = top[u];
    }
    
    if (dep[u] > dep[v]) swap(u, v);
    ans += queryQS(root[cc], 1, seg[0], seg[u], seg[v]);
    return ans;
}

int queryQM(int k, int l, int r, int li, int ri) {
    if (!k) return 0;
    if (l > ri || r < li) return 0;
    if (l >= li && r <= ri) return maxx[k];
    
    int mid = (l + r) >> 1;
    int ans = 0;
    if (mid >= li) ans = max(ans, queryQM(ls[k], l, mid, li, ri));
    if (mid < ri) ans = max(ans, queryQM(rs[k], mid + 1, r, li, ri));
    return ans;
}

int QM(int u, int v) {
    int ans = 0, cc = revc[seg[u]];
    int fu = top[u], fv = top[v];
    while (fu != fv) {
        if (dep[fu] < dep[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        ans = max(ans, queryQM(root[cc], 1, seg[0], seg[fu], seg[u]));
        u = father[fu];
        fu = top[u];
    }
    
    if (dep[u] > dep[v]) swap(u, v);
    ans = max(ans, queryQM(root[cc], 1, seg[0], seg[u], seg[v]));
    return ans;
}

void calc() {
    string line;
    getline(cin, line);
    char op[4];
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%s", op + 1);
        scanf("%d%d\n", &x, &y);
        if (!strcmp(op + 1, "CC")) {
            updateCC(x, y);
        } else if (!strcmp(op + 1, "CW")) {
            updateCW(x, y);
        } else if (!strcmp(op + 1, "QS")) {
            printf("%d\n", QS(x, y));
        } else {
            printf("%d\n", QM(x, y));
        }
    }
}

/*
题意为给定一棵树，对树上节点赋值+染色。每次操作更改点权或更改颜色，每次询问求路径最大值或路径权值和。

首先简化问题，假如没有染色的话，这就是树剖的板子题：把树上节点用树链剖分来映射到一段区间上，然后通过维护线段树来解决问题。不懂的见树剖讲解。

之后考虑如何染色。暴力的想法是，开色数棵线段树，但是一看不行，因为色数是10^5的。于是本能想到优化空间的好帮手：动态开点。对想法进行验证，发现每次操作并不需要完全使用所有节点，所以动态开点是完全可行的，每次修改的时空复杂度是𝑂(log𝑁)
，可过。

注意一下，有些同学说这个叫主席树，但是其实这个并不是主席树。主席树的特点是多棵线段树有共用节点。但是这道题并没有这个共用的点，每棵线段树是完全相互独立的。所以它不是主席树。

于是我们得出了结论：这道题是动态开点+树剖的板子题。（逃

于是这道题的难点变成了代码实现。需要注意的有几个点：

因为是多棵线段树，所以要开一个数组root来记录每棵线段树的根是谁。

因为是动态开点，所以一开始不需要建全树，对每个点进行修改即可。

因为权值都为正，所以在变更宗教的时候不需要把原来宗教的节点删除，直接置零即可。
*/
int main() {
    Read();
    
    dfs1(1, 0);
    seg[0] = seg[1] = top[1] = 1;
    revw[1] = w[1], revc[1] = c[1];
    dfs2(1);
    // initial for every religion
    for (int i = 1; i <= n; i++) {
        update1(root[c[i]], 1, seg[0], seg[i], w[i]);
    }
    
    calc();
    
    return 0;
}