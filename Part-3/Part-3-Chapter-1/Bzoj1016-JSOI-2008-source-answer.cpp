#include <bits/stdc++.h>

using namespace std;

const int N = 1010, M = 1010, mod = 31011;

int n, m;
struct Edge {
    int a, b, c;
} e[M];
int p[N], r[N];
int tot;
int cnt[N];
int S;

int find(int x) {
    while (p[x] != x)
        x = p[x];

    return x;
}

bool cmp(Edge a, Edge b) {
    return a.c < b.c;
}

void kruskal() {
    sort(e + 1, e + 1 + m, cmp);

    for (int i = 1; i <= n; ++ i)
        p[i] = i;

    int sum = 0;

    for (int i = 1; i <= m; ++ i) {
        if (e[i].c != e[i - 1].c)
            ++ tot ;

        r[tot] = i;
        int a = find(e[i].a), b = find(e[i].b);

        if (a != b) {
            p[a] = b;
            ++ cnt[tot] ;
            ++ sum ;
        }
    }

    if (sum < n - 1) {
        puts("0");
        exit(0);
    }
}

void dfs(int id, int now, int dep) {
    if (now > r[id]) {
        S += dep == cnt[id];
        return ;
    }

    dfs(id, now + 1, dep);
    int a = find(e[now].a), b = find(e[now].b);

    if (a != b) {
        p[a] = b;
        dfs(id, now + 1, dep + 1);
        p[a] = a;
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; ++ i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        e[i] = {a, b, c};
    }

    kruskal();

    for (int i = 1; i <= n; ++ i)
        p[i] = i;

    int res = 1;

    for (int i = 1; i <= tot; ++ i) {
        dfs(i, r[i - 1] + 1, 0);
        res = (res * S) % mod;
        S = 0;

        for (int j = r[i - 1] + 1; j <= r[i]; ++ j) {
            int a = find(e[j].a), b = find(e[j].b);
            p[a] = b;
        }
    }

    printf("%d\n", res);

    return 0;
}