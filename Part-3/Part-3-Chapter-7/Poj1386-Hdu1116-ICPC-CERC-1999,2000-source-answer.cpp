#include <bits/stdc++.h>
using namespace std;
const int L = 1e3 + 10;
int t, n;
char opt[L];
int g[30][30];
int ind[30], oud[30];
bool vis[30];
void init() {
    memset(g, 0, sizeof(g));
    memset(ind, 0, sizeof(ind));
    memset(oud, 0, sizeof(oud));
    memset(vis, 0, sizeof(vis));
}
void dfs(int x) {
    vis[x] = 1;

    for (int y = 1; y <= 26; y++) {
        if (g[x][y] && !vis[y])
            dfs(y);
    }
}
bool Connected() {
    for (int i = 1; i <= 26; i++)
        if ((ind[i] + oud[i]) != 0) {
            dfs(i);
            break;
        }

    for (int i = 1; i <= 26; i++)
        if ((ind[i] != 0 && oud[i] != 0) && !vis[i])
            return 0;

    return 1;
}
bool Euler_loop() {
    for (int i = 1; i <= 26; i++)
        if (ind[i] != oud[i])
            return 0;

    return 1;
}
bool Euler_path() {
    int s0 = 0, s1 = 0, s2 = 0;

    for (int i = 1; i <= 26; i++) {
        if (ind[i] == oud[i])
            s0++;

        if (ind[i] == oud[i] - 1)
            s1++;

        if (ind[i] == oud[i] + 1)
            s2++;
    }

    return s0 == 24 && s1 == 1 && s2 == 1;
}
int main() {
    scanf("%d", &t);

    while (t--) {
        init();
        scanf("%d", &n);

        for (int i = 1; i <= n; i++) {
            cin >> (opt + 1);
            int len = strlen(opt + 1);
            g[opt[1] - 'a' + 1][opt[len] - 'a' + 1] = 1;
            g[opt[len] - 'a' + 1][opt[1] - 'a' + 1] = 1;
            oud[opt[1] - 'a' + 1]++;
            ind[opt[len] - 'a' + 1]++;
            //          printf("%d %d\n",opt[1]-'a'+1,opt[len]-'a'+1);
        }

        if (!Connected()) {
            puts("The door cannot be opened.");
            continue;
        }

        if (!Euler_loop() && !Euler_path()) {
            puts("The door cannot be opened.");
            continue;
        }

        puts("Ordering is possible.");
    }

    return 0;
}