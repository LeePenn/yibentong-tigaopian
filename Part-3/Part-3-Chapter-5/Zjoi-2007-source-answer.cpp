#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
template<typename T>inline void read(T &x) {
    x = 0;
    int f = 1;
    char ch = getchar();

    while (ch < 48 || ch > 57) {
        if (ch == '-') {
            f = -1;
        }

        ch = getchar();
    }

    while (ch >= 48 && ch <= 57) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    x *= f;
}
template<typename T>inline void write(T x) {
    if (x < 0)
        putchar('-'), x = -x;

    if (x > 9)
        write(x / 10);

    putchar(x % 10 + 48);
}
const int N = 1e5 + 9;
const int M = 1E6 + 9;
int mod;
int h[N], ne[M], e[M], w[M], idx;
void add(int a, int b) {
    e[++idx] = b;
    ne[idx] = h[a];
    h[a] = idx;
}
int dfn[N], low[N], stk[N], tot, top, sum[N], col, co[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];

        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!co[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        col++;
        co[u] = col;
        int tmp;

        do {
            tmp = stk[top--];
            sum[col]++;
            co[tmp] = col;
        } while (u != tmp);
    }
}
int n, m;
int x[M], y[M];
bool cmp(int a, int b) {
    if (x[a] != x[b]) {
        return x[a] < x[b];
    }

    return y[a] < y[b];
}
int dis[N], nu[M];
int we;
void remove() {
    for (int i = 1; i <= m; i++) {
        nu[i] = i;
        x[i] = co[x[i]];
        y[i] = co[y[i]];

    }

    sort(nu + 1, nu + m + 1, cmp);
}
int de[N];
void build() {
    idx = 0;
    // memset(ne,0,sizeof(ne));
    memset(h, -1, sizeof(h));

    for (int i = 1; i <= m; i++) {
        int z = nu[i];

        if ((x[z] != y[z]) && (x[z] != x[nu[i - 1]] || y[z] != y[nu[i - 1]])) {
            add(x[z], y[z]);
            ++de[y[z]];
        }
    }
}
int ue[N];
int ans, anss;

void reset() {
    for (int i = 1; i <= col; i++) {
        if (!de[i]) {
            ue[++we] = i;
            dis[i] = sum[i];
            w[i] = 1;

            if (dis[ans] < dis[i])
                ans = i;
        }
    }
}
int t;
void topo() {
    while (t < we) {
        int u = ue[++t];

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            // if(u==v) continue;
            --de[v];

            if (dis[v] < dis[u] + sum[v]) {
                dis[v] = dis[u] + sum[v];
                w[v] = 0;

                if (dis[ans] < dis[v])
                    ans = v;
            }

            if (dis[v] == dis[u] + sum[v]) {
                w[v] = (w[v] + w[u]) % mod;

            }

            if (!de[v])
                ue[++we] = v;
        }
    }
}
void ask() {
    for (int i = 1; i <= n; i++) {
        if (dis[i] == dis[ans]) {
            anss = (anss + w[i]) % mod;
        }
    }
}
int main() {
    read(n), read(m), read(mod);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        read(x[i]), read(y[i]);
        add(x[i], y[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    remove();
    build();
    reset();
    topo();
    ask();
    printf("%d\n%d", dis[ans], anss);
    return 0;
}