/*
统计一张不一定联通的无向图中欧拉路径数量：
    用并查集维护联通性,一个联通块中的数量就是其中奇点个数/2,如果没有就是1
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int n, m;
int d[N], sz[N], cnt[N], f[N];  //度数，大小，奇点个数， 并查集的根结点

int find(int x) {
    if (f[x] != x)
        f[x] = find(f[x]);

    return f[x];
}

void init() {
    memset(d, 0, sizeof(d));
    memset(sz, 0, sizeof(sz));
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= n; i ++)
        f[i] = i;

}
int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        init();

        for (int i = 1; i <= m; i ++) {
            int u, v;
            scanf("%d %d", &u, &v);
            d[u] ++;
            d[v] ++;
            u = find(u);
            v = find(v);

            if (u != v)
                f[u] = v;
        }

        for (int u = 1; u <= n; u ++) {
            int x = find(u);
            sz[x] ++;

            if (d[u] & 1)
                cnt[x] ++;
        }

        int res = 0;

        for (int u = 1; u <= n; u ++) {
            if (sz[u] > 1) {
                if (cnt[u] == 0)
                    res ++;
                else
                    res += cnt[u] / 2;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
/*
3 3
1 1
2 2
3 3     0

3 3
1 1
2 2
1 2     0

1 1
1 1     1
0
*/