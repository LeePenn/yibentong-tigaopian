#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 500 + 10, M = 1000000;

struct Edge {
    int nxt, v;
    Edge() { nxt = v = 0; }
    Edge(int _nxt, int _v) {
        nxt = _nxt;
        v = _v;
    }
}edge[M];
int hd[N], etot;
int n, m;

void add_edge(int u, int v) {
    edge[++etot] = Edge(hd[u], v);
    hd[u] = etot;
}

int dfn[N], low[N], dfstime, st[N], top;
vector<int> scc[N];
int bt;
int root;
int cut[N];

void Tarjan(int u) {
    dfn[u] = low[u] = ++dfstime;
    st[++top] = u;
    int ch_cnt = 0;
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (!dfn[v]) {
            ch_cnt++;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if ((u == root && ch_cnt > 1) || (u != root && dfn[u] <= low[v])) {
                cut[u] = 1;
            }
            if (dfn[u] <= low[v]) {
                bt++;
                scc[bt].clear();
                do {
                    scc[bt].push_back(st[top--]);
                } while (st[top + 1] != v);
                scc[bt].push_back(u);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void solve() {
    etot = 0;
    n = 0;
    memset(hd, 0, sizeof(hd));
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        n = max(n, max(u, v));
        add_edge(u, v);
        add_edge(v, u);
    }
    
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(st, 0, sizeof(st));
    memset(cut, 0, sizeof(cut));
    dfstime = 0, top = 0, bt = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            Tarjan(i);
        }
    }   
    
    LL ans = 0, num = 1;
    for (int i = 1; i <= bt; i++) {
        int cut_num = 0;
        int len = scc[i].size();
        for (int j = 0; j < len; j++) {
            if (cut[scc[i][j]] == 1) {
                cut_num++;
            }
        }
        
        if (cut_num == 0) {
            ans += 2;
            num *= len * (len - 1) / 2;
        } else if (cut_num == 1) {
            ans++;
            num *= len - 1;
        }
    }
    
    printf("%lld %lld\n", ans, num);
}

int main() {
    int T = 1;
    while (scanf("%d", &m) == 1 && m) {
        printf("Case %d: ", T++);
        solve();
    }
}