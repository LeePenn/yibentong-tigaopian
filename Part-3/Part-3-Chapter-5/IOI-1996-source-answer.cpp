#include <bits/stdc++.h>
using namespace std;

const int N = 109, M = 1e4 + 9;
int n, m;

int h[N], to[M], ne[M], idx;
void add(int u, int v) {
    ++ idx;
    to[idx] = v;
    ne[idx] = h[u];
    h[u] = idx;
}

int dfn[N], low[N],
    timestamp;      //u结点的访问次序; 所在的强连通分量里，能够访问到的次序最小的结点
stack <int> stk;
bool in_stk[N];
int scc[N], cnt,
    sz[N];             //u结点所在强连通分量的编号、强连通分量的总数、每个强连通分量的大小
void tarjan(int u) {
    dfn[u] = low[u] = ++ timestamp;
    stk.push(u);
    in_stk[u] = true;

    for (int i = h[u]; i; i = ne[i]) {
        int v = to[i];

        if (!dfn[v]) {              //v是u的后代，u -> v是前向边
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {     //v是u的祖先(后向边)，或者和u没有祖先后代的关系(交叉边)
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
        } while (v != u);
    }
}

int in[N], out[N];                  //某个强连通分量的入度、出度
int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++) {
        int u;

        while (scanf("%d", &u) && u) {
            add(i, u);
        }
    }

    for (int u = 1; u <= n; u ++) {
        if (!dfn[u]) {
            tarjan(u);
        }
    }

    for (int u = 1; u <= n; u ++) {
        for (int i = h[u]; i; i = ne[i]) {
            int v = to[i];

            if (scc[u] != scc[v]) {
                out[scc[u]] ++;
                in[scc[v]] ++;
            }
        }
    }

    int p = 0, q = 0;

    for (int i = 1; i <= cnt; i ++) {
        if (!in[i])
            p ++;

        if (!out[i])
            q ++;
    }

    printf("%d\n", p);

    if (cnt == 1)
        puts("0");
    else
        printf("%d\n", max(p, q));

    return 0;
}