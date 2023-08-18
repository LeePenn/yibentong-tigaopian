#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
#define boo(i) bitset<i>
#define ri register int
#define rll register long long
#define ll long long
#define max_(i,j) (i<j?j:i)
#define min_(i,j) (i<j?i:j)
#define abs_(x) (x>0?x:(-x))
using namespace std;
int n, m;
int head[500001], nxt[1000001], to[1000001], len;
int mon[500001];
struct edg {
    int x, y;
} a[500001];
void add_l(int x, int y) {
    len++;
    to[len] = y;
    nxt[len] = head[x];
    head[x] = len;
}
int low[500001], dfn[500001], dfl;
bool in[500001];
int st[500001], l;
int siz[500001];
int sy[500001];
bool bar[500001];
void tar(int x) {
    low[x] = dfn[x] = ++dfl;
    in[x] = true;
    l++;
    st[l] = x;

    for (int i = head[x]; i; i = nxt[i]) {
        if (!dfn[to[i]]) {
            tar(to[i]);
            low[x] = min(low[x], low[to[i]]);
        } else {
            if (in[to[i]]) {
                low[x] = min(low[x], dfn[to[i]]);
            }
        }
    }

    if (low[x] == dfn[x]) {
        int t;

        do {
            t = st[l];
            l--;
            in[t] = false;
            sy[t] = x;
            siz[x] += mon[t];
            bar[x] |= bar[t];
        } while (t != x);
    }
}
vector<int>ne[500001];
queue<int>q;
int sh[500001];
int cen;
void addn() {
    for (int i = 1; i <= m; i++) {
        if (sy[a[i].x] != sy[a[i].y]) {
            ne[sy[a[i].x]].push_back(sy[a[i].y]);
        }
    }
}
void spf() {
    q.push(sy[cen]);
    sh[sy[cen]] = siz[sy[cen]];

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        in[t] = false;

        for (int i = 0; i < ne[t].size(); i++) {
            if (sh[ne[t][i]] < sh[t] + siz[ne[t][i]]) {
                sh[ne[t][i]] = sh[t] + siz[ne[t][i]];

                if (!in[ne[t][i]]) {
                    in[ne[t][i]] = true;
                    q.push(ne[t][i]);
                }
            }
        }
    }

    int maxn = 0;

    for (int i = 1; i <= n; i++) {
        //printf("%d\n",sh[i]);
        if (bar[i]) {
            maxn = max(maxn, sh[i]);
        }
    }

    printf("%d", maxn);
}
int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
        add_l(a[i].x, a[i].y);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &mon[i]);
    }

    int p;
    scanf("%d%d", &cen, &p);

    for (int i = 1, x; i <= p; i++) {
        scanf("%d", &x);
        bar[x] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tar(i);
        }
    }

    addn();
    spf();
}