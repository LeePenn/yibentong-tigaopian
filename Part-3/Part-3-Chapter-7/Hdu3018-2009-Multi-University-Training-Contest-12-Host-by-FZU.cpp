#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int fa[N];
int n, m;
int in[N], out[N];
int cnt[N], sz[N];

void init() {
    for (int i = 1; i <= n; i++) fa[i] = i;
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(cnt, 0, sizeof(cnt));
    memset(sz, 0, sizeof(sz));
}

int find(int x) {
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            in[v]++, out[u]++;
            u = find(u);
            v = find(v);
            if (u != v) fa[v] = u;
        }
        
        for (int i = 1; i <= n; i++) {
            int u = find(i);
            sz[u]++;
            if ((in[i] + out[i]) & 1) cnt[u]++;
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            // 可能只有1个点
            if (sz[i] > 1) {
                if (cnt[i] == 0) {
                    ans++;
                } else {
                    ans += cnt[i] / 2;
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}