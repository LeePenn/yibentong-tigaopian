#include <bits/stdc++.h>
using namespace std;
int k, t;
bool vis[1 << 12][2];
void dfs(int x) {
    for (int i = 0; i <= 1; i++) {
        if (vis[x][i])
            continue;

        vis[x][i] = 1;
        printf("%d", i);
        dfs(((x << 1)&t) | i);
    }
}
int main() {
    scanf("%d", &k);
    printf("%d ", 1 << k);
    t = (1 << k - 1) - 1;
    dfs(t);
    return 0;
}