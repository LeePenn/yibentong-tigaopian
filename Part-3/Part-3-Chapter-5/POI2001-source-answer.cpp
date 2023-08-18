#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 4e6 + 666;
int n;
int head[N], to[N], nxt[N], l;
int dfn[N], low[N], sy[N], dfl, cnt;
int st[N], len;
inline void tarj(register int num) {
    dfn[num] = low[num] = ++dfl;
    st[++len] = num;

    for (int i = head[num]; i; i = nxt[i]) {
        if (!dfn[to[i]]) {
            tarj(to[i]);
            low[num] = min(low[num], low[to[i]]);
        } else {
            if (!sy[to[i]]) {
                low[num] = min(low[num], dfn[to[i]]);
            }
        }
    }

    if (dfn[num] == low[num]) {
        int t;
        cnt++;

        do {
            t = st[len--];
            sy[t] = cnt;
        } while (t != num);
    }
}
inline void add_l(register int x, register int y) {
    l++;
    to[l] = y;
    nxt[l] = head[x];
    head[x] = l;
}
#define p(i) ((i&1)?i+1:i-1)
int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        add_l(x, p(y));
        add_l(y, p(x));
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) {
            tarj(i);
        }
    }

    for (int i = 1; i <= 2 * n; i += 2) {
        if (sy[i] == sy[i + 1]) {
            printf("NIE");
            return 0;
        }
    }

    //printf("POSSIBLE\n");
    for (int i = 1; i <= 2 * n; i += 2) {
        if (sy[i] > sy[i + 1]) {
            printf("%d\n", i + 1);
            continue;
        }

        printf("%d\n", i);
    }
}