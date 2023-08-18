/**
 * @Author: Yang Li
 * @Date:   2022-08-12 07:05:35
 * @Last Modified by:   Yang Li
 * @Last Modified time: 2022-12-29 15:38:40
 */
# include <iostream>
# include <cstring>
# include <algorithm>
# include <string>
# include <cmath>
# include <vector>
# include <queue>
# include <map>
# include <bitset>
# include <stack>
# include <deque>
# include <list>
# include <set>

# define ui unsigned int
# define ll long long
# define ull unsigned long long
# define ulli unsigned long long int

using namespace std;

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int VV = 505;
const int P = 100003;
const double inff = 0x3f3f3f3f3f;
const ll inf = 1e9;
const int INF = 0x3f3f3f3f;
const ll infff = (1ll << 31) - 1;
const ll mod = 1e9 + 7;
const ull mod1 = 19260817;
const ull mod2 = 19660813;
const ll mod3 = 998244353;
const int mod4 = 19260817;
const ull base = 131;
const double eps = 1e-7;
const double lorry = (sqrt(5.0) + 1.0) / 2.0;
const double Pi = acos(-1.0);

template<typename T>
void read(T &x) {
    T f = 1;
    x = 0;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        // x %= mod4;
        c = getchar();
    }

    x *= f;
}

int n, q, x, y;
int w[N], c[N];
char op[4];

struct edge {
    int from, next, to;
} e[M << 1];

int head[N], num;

void add(int u, int v) {
    e[++num] = (edge) {
        u, head[u], v
    };
    head[u] = num;
}

int d[N], f[N], son[N], siz[N], top[N], id[N], wt[N], ct[N], cnt;

void dfs1(int u, int fa, int dep) {
    f[u] = fa;
    d[u] = dep;
    siz[u] = 1;
    int maxson = -1;

    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;

        if (v == fa)
            continue;

        dfs1(v, u, dep + 1);
        siz[u] += siz[v];

        if (maxson < siz[v])
            son[u] = v, maxson = siz[v];
    }
}

void dfs2(int u, int topf) {
    id[u] = ++cnt;
    wt[cnt] = w[u];
    ct[cnt] = c[u];
    top[u] = topf;

    if (!son[u])
        return ;

    dfs2(son[u], topf);

    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;

        if (v == f[u] || v == son[u])
            continue;

        dfs2(v, v);
    }
}

int root[N];
int ls[N * 20], rs[N * 20], sum[N * 20], mx[N * 20], ind;

void pushup(int rt) {
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    mx[rt] = max(mx[ls[rt]], mx[rs[rt]]);
}

void update(int &rt, int l, int r, int v, int x) {
    // 将第v个数修改为x
    if (!rt)
        rt = ++ind;

    if (l == r) {
        sum[rt] = mx[rt] = x;
        return ;
    }

    int m = (l + r) >> 1;

    if (v <= m)
        update(ls[rt], l, m, v, x);
    else
        update(rs[rt], m + 1, r, v, x);

    pushup(rt);
}

void CC(int x, int c) {
    int cc = ct[id[x]];
    ct[id[x]] = c;
    update(root[cc], 1, n, id[x], 0);
    update(root[c], 1, n, id[x], wt[id[x]]);
}

void CW(int x, int ww) {
    int cc = ct[id[x]];
    wt[id[x]] = ww;
    update(root[cc], 1, n, id[x], ww);
}

int queryS(int rt, int L, int R, int l, int r) {
    if (!rt)
        return 0;

    if (L <= l && r <= R)
        return sum[rt];

    int m = (l + r) >> 1;
    int ans = 0;

    if (L <= m)
        ans += queryS(ls[rt], L, R, l, m);

    if (R > m)
        ans += queryS(rs[rt], L, R, m + 1, r);

    return ans;
}

int queryM(int rt, int L, int R, int l, int r) {
    if (!rt)
        return 0;

    if (L <= l && r <= R)
        return mx[rt];

    int m = (l + r) >> 1;
    int ans = 0;

    if (L <= m)
        ans = max(ans, queryM(ls[rt], L, R, l, m));

    if (R > m)
        ans = max(ans, queryM(rs[rt], L, R, m + 1, r));

    return ans;
}

int QM(int x, int y) {
    int ans = 0, cc = ct[id[x]];

    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);

        ans = max(ans, queryM(root[cc], id[top[x]], id[x], 1, n));
        x = f[top[x]];
    }

    if (d[x] < d[y])
        swap(x, y);

    ans = max(ans, queryM(root[cc], id[y], id[x], 1, n));
    return ans;
}

int QS(int x, int y) {
    int ans = 0, cc = ct[id[x]];

    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);

        ans += queryS(root[cc], id[top[x]], id[x], 1, n);
        x = f[top[x]];
    }

    if (d[x] < d[y])
        swap(x, y);

    ans += queryS(root[cc], id[y], id[x], 1, n);
    return ans;
}

int main() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        read(w[i]), read(c[i]);

    for (int i = 1; i < n; i++) {
        read(x), read(y);
        add(x, y), add(y, x);
    }

    dfs1(1, 0, 0);
    dfs2(1, 1);

    for (int i = 1; i <= n; i++)
        update(root[c[i]], 1, n, id[i], w[i]);

    while (q--) {
        scanf("%s %d %d", op, &x, &y);

        if (!strcmp(op, "CC"))
            CC(x, y);
        else if (!strcmp(op, "CW"))
            CW(x, y);
        else if (!strcmp(op, "QS"))
            printf("%d\n", QS(x, y));
        else
            printf("%d\n", QM(x, y));
    }

    return 0;
}