#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define boo(i) bitset<i>
#define ri register int
#define rll register long long
#define ll long long
#define max_(i,j) (i<j?j:i)
#define min_(i,j) (i<j?i:j)
#define abs_(x) (x>0?x:(-x))
using namespace std;
int n;
int head[200001], nxt[1000001], to[1000001], len;
void add_l(int x, int y) {
    len++;
    to[len] = y;
    nxt[len] = head[x];
    head[x] = len;
}
int low[200001], dfn[200001], st[200001], l, sl;
int sta, en;
bool cou[200001];
void tar(int x) {
    l++;
    low[x] = dfn[x] = l;

    for (int i = head[x]; i; i = nxt[i]) {
        if (!dfn[to[i]]) {
            tar(to[i]);
            low[x] = min(low[x], low[to[i]]);

            if (low[to[i]] >= dfn[x] && x != sta && dfn[en] >= dfn[to[i]]) {
                cou[x] = true;
            }
        } else {
            low[x] = min(low[x], dfn[to[i]]);
        }
    }
}
int main() {
    scanf("%d", &n);
    int x, y;
    scanf("%d%d", &x, &y);

    while (x != 0 && y != 0) {
        add_l(x, y);
        add_l(y, x);
        scanf("%d%d", &x, &y);
    }

    scanf("%d%d", &sta, &en);
    tar(sta);

    for (int i = 1; i <= n; i++) {
        if (cou[i]) {
            printf("%d", i);
            return 0;
        }
    }

    printf("No solution");
}