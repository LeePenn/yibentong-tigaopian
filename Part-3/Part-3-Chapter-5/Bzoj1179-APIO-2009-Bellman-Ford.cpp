#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 9, M = 2 * N;
int n, m, s, p;

int a[N], f1[N];            //每个点代表的现金，是否有酒吧
int sum[N], maxx[N],
    f2[N]; //SCC内的现金之和，从起点出发经过的最多现金，SCC内是否有酒吧
inline char get() {
    const int TOP = 1000000;
    static char T[TOP], *x = T, *y = T;
    return x == y && (y = (x = T) + fread(T, 1, TOP, stdin), x == y) ? EOF : *x++;
}
inline void read(int &num) {
    register int sign = 1;
    register char c;

    while (((c = get()) < '0' || c > '9') && c != '-')
        ;

    c == '-' ? num = sign = 0 : num = c - 48;

    while ((c = get()) >= '0' && c <= '9')
        num = (num << 3) + (num << 1) + (c - 48);

    num = sign ? num : -num;
}

int h[N], hscc[N], to[M], ne[M], idx;
void add(int h[], int u, int v) {
    ++ idx;
    to[idx] = v;
    ne[idx] = h[u];
    h[u] = idx;
}

int dfn[N], low[N], timestamp;
stack <int> stk;
bool in_stk[N];
int cnt, scc[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++ timestamp;
    stk.push(u);
    in_stk[u] = true;

    for (int i = h[u]; i; i = ne[i]) {
        int v = to[i];

        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if (dfn[u] == low[u]) {
        cnt ++;
        int v;

        do {
            v = stk.top();
            stk.pop();
            in_stk[v] = false;
            scc[v] = cnt;

            if (f1[v] == 1)
                f2[scc[v]] = 1;

            sum[scc[v]] += a[v];
        } while (v != u);
    }
}

int main() {
    read(n);
    read(m);

    for (int i = 1; i <= m; i ++) {
        int u, v;
        read(u);
        read(v);
        add(h, u, v);
    }

    for (int i = 1; i <= n; i ++)
        read(a[i]);

    read(s);
    read(p);

    for (int i = 1; i <= p; i ++) {
        int x;
        read(x);
        f1[x] = 1;
    }

    tarjan(s);

    for (int u = 1; u <= n; u ++) {
        for (int i = h[u]; i; i = ne[i]) {
            int v = to[i];

            if (scc[u] != scc[v]) {
                add(hscc, scc[u], scc[v]);
            }
        }
    }

    maxx[cnt] = sum[cnt];

    for (int u = cnt; u >= 1; u --) {
        for (int i = hscc[u]; i; i = ne[i]) {
            int v = to[i];
            maxx[v] = max(maxx[v], maxx[u] + sum[v]);
        }
    }

    int ans = 0;

    for (int u = cnt; u >= 1; u --) {
        if (f2[u] == 1) {
            ans = max(ans, maxx[u]);
        }
    }

    printf("%d", ans);

    return 0;
}






