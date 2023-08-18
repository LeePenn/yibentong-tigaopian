#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, M = 1e5 + 10;
struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int ans;
int n, m;

int dfn[N], low[N], dfstime;
int cut[N];

void init() {
    etot = 0, dfstime = 0, ans = 0;
    memset(hd, 0, sizeof(hd));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(cut, 0, sizeof(cut));
}

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int root;

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    int num = 0;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            // 这里和求割点的模板题不一样，如果u == root，那么删掉u，就剩下子树部分，如果子树只有一个num = 1，否则分成2部分
            if (dfn[u] <= low[v]) {
                num++;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    // 如果u != root，删掉后要算上u祖先那部分
    if (u != root) num++;
    ans = max(ans, num);
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u++, v++;
            add_edge(u, v);
            add_edge(v, u);
        }
        
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                // cnt代表联通块
                cnt++;
                root = i;
                Tarjan(i);
            }
        }
        
        printf("%d\n", ans + cnt - 1);
    }

    return 0;
}