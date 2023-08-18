#include <bits/stdc++.h>
using namespace std;
const int N = 1000 + 10;
int m;
bool exist[N];
int in[N], out[N];
int fa[N];
int num[N];

int find(int u) {
    if (fa[u] != u) fa[u] = find(fa[u]);
    return fa[u];
}

int main() {
    for (int i = 1; i < N; i++) fa[i] = i;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        out[u]++, in[v]++;
        exist[u] = true;
        exist[v] = true;
        u = find(u), v = find(v);
        if (u != v) fa[v] = u;
    }
    
    for (int i = 1; i < N; i++) {
        if (exist[i]) {
            // 有向图环只需统计入度或出度
            if (in[i] < out[i]) num[find(i)] += out[i] - in[i];
        }
    }
    
    int ans = 0;
    for (int i = 1; i < N; i++) {
        if (!exist[i]) continue;
        if (fa[i] == i) {
            // 补全环
            if (num[i]) {
                ans += num[i];
            } else {
                // 统计的是点的长度
                ans++;
            }
        }
    }
    
    printf("%d\n", ans + m);
    
    return 0;
}