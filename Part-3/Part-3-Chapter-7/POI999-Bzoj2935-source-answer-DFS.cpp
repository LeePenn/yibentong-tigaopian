#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, m;
vector<int> g[N];
int ind[N], oud[N];
bool exist[N];
bool vis[N];
int sum;
void dfs(int x) {
    vis[x] = 1;

    if (ind[x] > oud[x])
        sum += ind[x] - oud[x];

    for (int i = 0; i < g[x].size(); i++) {
        int y = g[x][i];

        if (vis[y])
            continue;

        dfs(y);
    }
}
int main() {
    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
        oud[x]++, ind[y]++;
        exist[x] = exist[y] = 1;
        n = max(n, max(x, y));
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (!exist[i])
            continue;

        if (!vis[i]) {
            sum = 0;
            dfs(i);
            ans += max(sum, 1);
        }
    }

    printf("%d", ans + m);
    return 0;
}