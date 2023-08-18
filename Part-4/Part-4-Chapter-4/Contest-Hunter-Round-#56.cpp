#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10, M = 1e6 + 10, LOGN = 25;

int n, m;
struct Edge {
    int nxt, v, w;
    Edge() { nxt = v = w = 0; }
    Edge(int _nxt, int _v, int _w) {
        nxt = _nxt;
        v = _v;
        w = _w;
    }
}edge[M];
int hd[N], etot;
int dep[N], f[N][LOGN];
int node2time[N], time2node[N], dfstime;
LL ans, dist_root[N];

void add_edge(int x, int y, int z) {
    edge[++etot] = Edge(hd[x], y, z);
    hd[x] = etot;
}

void Read() {
    scanf("%d", &n);
    int x, y, z;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z); add_edge(y, x, z);
    }
}

void Dfs1(int u, int pa) {
    dep[u] = dep[pa] + 1;
    node2time[u] = ++dfstime;
    time2node[dfstime] = u;
    for (int i = 0; i <= 21; i++) {
        f[u][i + 1] = f[f[u][i]][i];
    }
    
    for (int i = hd[u]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == pa) continue;
        f[v][0] = u;
        dist_root[v] = dist_root[u] + (LL)edge[i].w;
        Dfs1(v, u);
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 21; ~i; i--) {
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
        if (u == v) return u;
    }
    
    for (int i = 21; ~i; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

LL dist(int u, int v) {
    return dist_root[u] + dist_root[v] - (LL)2 * dist_root[LCA(u, v)];
}

set<int> st;

void work() {
    scanf("%d\n", &m);
    char op;
    string line;
    int x;
    for (int i = 1; i <= m; i++) {
        scanf("%c", &op);
        if (op == '+') {
            scanf("%d\n", &x);
            if (st.size()) {
                int cur_time = node2time[x];
                set<int>::iterator pos = st.lower_bound(cur_time);
                int nxt, pre;
                if (cur_time < *st.begin()) {
                    nxt = *st.begin();
                    pre = *(--st.end());
                } else if (cur_time > *(--st.end())) {
                    nxt = *st.begin();
                    pre = *(--st.end());
                } else {
                    nxt = *st.lower_bound(cur_time);
                    pre = *(--st.lower_bound(cur_time));
                }
                ans += dist(x, time2node[nxt]) + dist(x, time2node[pre]) - dist(time2node[nxt], time2node[pre]);
            }
            st.insert(node2time[x]);
        } else if (op == '-') {
            scanf("%d\n", &x);
            int cur_time = node2time[x];
            set<int>::iterator l, r = st.lower_bound(cur_time);
            l = r;
            int nxt, pre;
            nxt = (r == (--st.end())) ? *(st.begin()) : *(++r);
            pre = (l == st.begin()) ? *(--st.end()) : *(--l);
            ans -= dist(x, time2node[nxt]) + dist(x, time2node[pre]) - dist(time2node[nxt], time2node[pre]);
            st.erase(cur_time);
        } else if (op == '?') {
            printf("%lld\n", ans / (LL)2);
            getline(cin, line);
        }  
    }
}

int main() {
    Read();
    Dfs1(1, 0);
    
    work();
    return 0;
}