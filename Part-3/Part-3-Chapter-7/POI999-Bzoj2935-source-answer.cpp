#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5, M = 4e6 + 5, MDEP = log2(N) + 1, inf = (1ll << 30);
int n, ans, num[N];
int in[N], out[N];
bool flag[N];
inline int r() {
    char ch = getchar();
    int x = 0, w = 1;

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();

    return w == 1 ? x : -x;
}
int id, h[N];
struct edge {
    int to, nt, u;
} e[M];
inline void add(int x, int y) {
    e[++id].to = y;
    e[id].u = x;
    e[id].nt = h[x];
    h[x] = id;
}
int fa[N];
inline int find_fa(int x) {
    return fa[x] == x ? x : fa[x] = find_fa(fa[x]);
}
inline void add_fa(int x, int y) {
    fa[find_fa(y)] = find_fa(x);
}
signed main() {
    n = r();

    for (int i = 1; i <= 1e3; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++) {
        int x = r(), y = r();
        in[y]++;
        out[x]++;
        flag[x] = flag[y] = 1;
        add_fa(x, y);
    }

    for (int i = 1; i <= 1e3; i++)
        if (flag[i])
            if (in[i] < out[i])
                num[find_fa(i)] += out[i] - in[i];

    for (int i = 1; i <= 1e3; i++)
        if (flag[i]) {
            if (find_fa(i) == i) {
                if (num[i])
                    ans += num[i];
                else
                    ans++;
            }
        }

    cout << ans + n;
    return 0;
}
/*

*/