#include <bits/stdc++.h>
using namespace std;

const int N = 100 + 10, M = 1000 + 10, MOD = 31011;
int n, m;
struct E {
    int u, v, c;
    bool operator <(const E &rh) const {
        return c < rh.c;
    }
}e[M];
int fa[N], l[M], cnt[M], tot;
int s;

int find(int x) {
    if (fa[x] != x) x = find(fa[x]);
    return fa[x];
}

void dfs(int idx, int now, int t) {
    if (now > l[idx]) {
        s += t == cnt[idx];
        return;
    }
    
    dfs(idx, now + 1, t);
    int u = find(e[now].u), v = find(e[now].v);
    if (u != v) {
        fa[v] = u;
        dfs(idx, now + 1, t + 1);
        fa[v] = v;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].c);
    }
    sort(e + 1, e + m + 1);
    
    for (int i = 1; i <= n; i++) fa[i] = i;
    
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        if (e[i].c != e[i - 1].c) {
            tot++;
        }
        l[tot] = i;
        int u = find(e[i].u), v = find(e[i].v);
        if (u != v) {
            fa[v] = u;
            cnt[tot]++;
            sum++;
        }
    }

    if (sum < n - 1) {
        printf("0\n");
        return 0;
    }
    
    for (int i = 1; i <= n; i++) fa[i] = i;
    
    int ans = 1;
    for (int i = 1; i <= tot; i++) {
        dfs(i, l[i - 1] + 1, 0);
        
        ans = (ans * s) % MOD;
        for (int j = l[i - 1] + 1; j <= l[i]; j++) {
            int u = find(e[j].u), v = find(e[j].v);
            if (u != v) {
                fa[v] = u;
            }
        }
        s = 0;
    }
    
    printf("%d\n", ans);


    return 0;
}