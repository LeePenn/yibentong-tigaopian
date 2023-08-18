#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 5e5 + 5;

int n, m;
int cnt;
int head[N];
int dfn[N];
int low[N];
int num;
int root;
long long ans[N], sz[N];
bool cut[N];

struct Node {
    int to;
    int next;
} e[M * 2];

void add(int u, int v) {
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
    cnt++;
}

void init() {
    cnt = 0;
    num = 0;
    memset(head, -1, sizeof head);
    memset(low, 0, sizeof low);
    memset(dfn, 0, sizeof dfn);
}

void tarjan(int u) {
    int c = 0;
    low[u] = dfn[u] = ++num;
    sz[u] = 1;
    ans[u] = 0;
    int sum = 0;

    for (int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].to;

        if (!dfn[v]) {
            tarjan(v);
            sz[u] += sz[v];
            low[u] = min(low[v], low[u]);

            if (low[v] >= dfn[u]) {
                c++;

                if (u != root || c > 1) {
                    // cout << "Cut : " << u << endl;
                    cut[u] = true;
                }

                ans[u] += (long long)sz[v] * (n - sz[v]);
                sum += sz[v];
            }
        } else {
            low[u] = min(dfn[v], low[u]);
        }
    }

    if (cut[u]) {
        ans[u] += (long long)(n - sum - 1) * (sum + 1) + n - 1;
    } else {
        ans[u] = 2 * n - 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    init();
    int u, v;

    while (m--) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
/*
7 9
1 2
2 3
3 4
3 5
4 5
4 2
1 6
7 1
6 7
*/