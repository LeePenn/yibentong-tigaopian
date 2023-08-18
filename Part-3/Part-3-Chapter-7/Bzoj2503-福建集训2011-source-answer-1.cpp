#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5, M = 2e5 + 5;
int n, m, a, b, d[N], tot, head[N], out[N], id[N], cnt1[N], cnt2[N], cnt;
struct Edge {
    int to, next;
} e[M << 1];
void add(int u, int v) {
    e[++tot].next = head[u], e[tot].to = v, head[u] = tot;
    return;
}
void dfs(int node) { // 也可用并查集
    id[node] = cnt; // 区分不同的连通块

    for (int i = head[node]; i; i = e[i].next) {
        int y = e[i].to;

        if (!id[y]) {
            dfs(y);
        }
    }

    return;
}
int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &a, &b);

        if (!a)
            a = ++n; // 为孤立的点建点配对

        if (!b)
            b = ++n;

        d[a]++;
        d[b]++;
        add(a, b);
        add(b, a);
    }

    if (!n) { // 没有点就把所有边连起来
        printf("%d", m);
    } else {
        for (int i = 1; i <= n; i++) {
            if (!id[i] && d[i]) {
                cnt++;
                dfs(i); // 染出不同的联通块，也可用并查集
            }
        }

        int odd = 0, even = 0, over = 0;

        // 分别代表：奇点数，偶点数，入度超过 2 的点数
        for (int i = 1; i <= n; i++) {
            if (!d[i]) {
                continue;
            }

            if (d[i] & 1) {
                cnt1[id[i]] = true; // 该块有奇点
                odd++; // 统计奇点
            }

            if (d[i] > 2) {
                cnt2[id[i]] = true; // 该块有入度大于二的点
                over++; // 统计入度大于二的点
            }
        }

        for (int i = 1; i <= cnt; i++) {
            if (!cnt1[i]) {
                if (!cnt2[i]) { // 该联通块仅有入度为 2 的点（是个环）
                    even += 2; // 拆环 + 熔合
                } else {
                    even++; // 熔合
                }
            }
        }

        int ans = (odd >> 1) + even + over;
        // 奇点两两融合，偶点可能熔合或拆环，入度大于二的点必须熔掉
        printf("%d", ans);
    }

    return 0;
}