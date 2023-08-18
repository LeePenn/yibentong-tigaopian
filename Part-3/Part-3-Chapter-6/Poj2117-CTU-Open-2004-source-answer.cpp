#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
using namespace std;
/*
无向图点的双连通分量，仍然用tarjan算法来做（求割点），对于割点有两种可能：
1.为根节点且有两个或以上子树
2.不为根结点
*/
const int N = 10010, M = 30010;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], cnt, res, timestamp, root;
int n, m;
void add(int u, int v) {
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    int cnt = 0;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];

        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);

            if (low[j] >= dfn[u])
                cnt++;
        } else
            low[u] = min(low[u], dfn[j]);
    }

    if (u != root && cnt)
        cnt++;

    res = max(res, cnt);
}
int main() {
    while (cin >> n >> m, n || m) {
        memset(h, -1, sizeof h);
        memset(dfn, 0, sizeof dfn);
        idx = 0;
        int u, v;

        while (m--) {
            scanf("%d%d", &u, &v);
            add(u, v), add(v, u);
        }

        cnt = 0, res = 0;

        for (root = 0; root < n; ++root) {
            if (!dfn[root]) {
                cnt++;
                tarjan(root);
            }
        }

        cout << res + cnt - 1 << endl;
    }

    return 0;
}