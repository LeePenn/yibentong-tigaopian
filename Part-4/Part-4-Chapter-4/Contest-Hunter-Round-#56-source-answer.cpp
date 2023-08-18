// 倍增求LCA详见：洛谷P3258(松鼠的新家)
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int Maxn = 1e5 + 5;
struct Edge {
    int to, nex, w;
} edge[Maxn * 2];
int head[Maxn];
int n, m, cnt = 0, tot = 0;
int node_id[Maxn], id_node[Maxn], depth[Maxn], logg[Maxn], p[Maxn][50];
LL ans, dis_root[Maxn];
void add_edge(int u, int v, int w) {
    cnt++;
    edge[cnt].to = v;
    edge[cnt].nex = head[u];
    edge[cnt].w = w;
    head[u] = cnt;
}
void dfs(int u, int f) {        // 标记dfs序，找距离最近的点
    id_node[++tot] = u;
    node_id[u] = tot;           // 只标记了一个时间戳

    for (int i = head[u]; i; i = edge[i].nex) {
        int v = edge[i].to;

        if (v == f)
            continue;

        dfs(v, u);
    }
}
void build(int u, int f) {      // dfs下降，倍增求祖先
    depth[u] = depth[f] + 1;    // 并求每个点到根的路径长度
    p[u][0] = f;

    for (int i = 1; i <= logg[depth[u]]; i++)
        p[u][i] = p[p[u][i - 1]][i - 1];

    for (int i = head[u]; i; i = edge[i].nex) {
        int v = edge[i].to;

        if (v == f)
            continue;

        dis_root[v] = dis_root[u] + edge[i].w;
        build(v, u);
    }
}
int LCA(int x, int y) {          // 倍增求LCA
    if (depth[x] < depth[y])
        swap(x, y);

    for (int i = logg[depth[x]]; i >= 0; i--) {
        if (depth[y] <= depth[p[x][i]])
            x = p[x][i];

        if (x == y)
            return x;
    }

    for (int i = logg[depth[x]]; i >= 0; i--)
        if (p[y][i] != p[x][i])
            x = p[x][i], y = p[y][i];

    return p[x][0];
}
void init() {
    depth[1] = 1;

    for (int i = 2; i <= n; i++)
        logg[i] = logg[i >> 1] + 1;

    build(1, 0);
}
LL dis(int u, int v) {          // 求两点的路径长度
    return dis_root[u] + dis_root[v] - 2ll * dis_root[LCA(u, v)];
}
set<int> st;
int main() {
    cin >> n;

    for (int i = 1, u, v, w; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    init();
    dfs(1, 0);
    cin >> m;

    for (int i = 1, t; i <= m; i++) {
        char ch[5];
        scanf("%s", ch);

        if (ch[0] == '+') {
            scanf("%d", &t);

            if (st.size()) {
                // lower_bound求出比我大的点中最小的点
                set<int >::iterator pos = st.lower_bound(node_id[t]);
                int nxt, pre;

                if (node_id[t] < *st.begin()) {
                    nxt = *st.begin();
                    pre = *(--st.end());
                } else if (node_id[t] > *(--st.end())) {
                    nxt = *(--st.end());
                    pre = *st.begin();
                } else {
                    nxt = *st.lower_bound(node_id[t]);
                    pre = *(--st.lower_bound(node_id[t]));
                }

                ans += (dis(t, id_node[nxt]) + dis(t, id_node[pre]) - dis(id_node[pre], id_node[nxt]));
            }

            st.insert(node_id[t]);
        } else if (ch[0] == '-') {
            scanf("%d", &t);
            set<int >::iterator l, r = st.lower_bound(node_id[t]);
            l = r;
            int nxt = (r == (--st.end())) ? *st.begin() : *(++r), pre = (l == st.begin()) ? *(--st.end()) : *(--l);
            ans -= (dis(t, id_node[pre]) + dis(t, id_node[nxt]) - dis(id_node[nxt], id_node[pre]));
            st.erase(node_id[t]);
        } else if (ch[0] == '?')
            printf("%lld\n", ans / 2ll);
    }

    return 0;
}