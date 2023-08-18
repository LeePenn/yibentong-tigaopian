#include <bits/stdc++.h>
using namespace std;

const int M = 1e6 + 10;
int n, m;
int du[M];
int fa[M], cnt;
int cnt1[M], cnt2[M];
bool flag[M];

int find(int i) {
    if (fa[i] != i) fa[i] = find(fa[i]);
    return fa[i];
}
    
int main() {    
    for (int i = 1; i < M; i++) fa[i] = i;

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (!u) u = ++n;
        if (!v) v = ++n;
        du[u]++, du[v]++;
        
        u = find(u), v = find(v);
        if (u != v) {
            fa[v] = u;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (du[i] && find(i) == i) {
            cnt++;
        }
    }
    
    if (cnt == 1) {
        int odd = 0, over = 0;
        for (int i = 1; i <= n; i++) {
            if (du[i] > 2) over++;
            if (du[i] & 1) odd++;
        }
        printf("%d\n", over + odd / 2);
    } else {
        
        // point
        for (int i = 1; i <= n; i++) {
            if (du[i] > 2) {
                cnt2[find(i)]++;
                flag[find(i)] = true;
            } 
            if (du[i] & 1) {
                cnt1[find(i)]++;
            }
        }
        // block
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (du[i] && find(i) == i) {
                if (cnt1[i]) {
                    ans += cnt2[i] + cnt1[i] / 2 - 1;
                } else {
                    ans += cnt2[i] + (!flag[i]);
                }
            }
        }        
        printf("%d\n", ans + cnt);
    }

    return 0;
}