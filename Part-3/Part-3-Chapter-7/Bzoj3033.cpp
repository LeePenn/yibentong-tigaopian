#include <bits/stdc++.h>
using namespace std;

int k, tot;
bool vis[1 << 12][2];

void dfs(int u) {
    for (int i = 0; i <= 1; i++) {
        if (vis[u][i]) continue;
        vis[u][i] = true;
        printf("%c", i + '0');
        int v = ((u << 1) & tot) | i;
        dfs(v);
    }
}

int main() {
    cin >> k;
    tot = (1 << (k - 1)) - 1;
    printf("%d ", 1 << k);
    dfs(tot);
    printf("\n");

    return 0;
}