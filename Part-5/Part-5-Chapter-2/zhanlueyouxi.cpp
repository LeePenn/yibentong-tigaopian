#include <bits/stdc++.h>
using namespace std;
const int N = 1500 + 10;
int n;
vector<int> g[N];
int f[N][2];
int rt;

void Read() {
    scanf("%d", &n);
    int u, k, v;
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &u, &k);
        for (int j = 1; j <= k; ++j) {
            scanf("%d", &v);
            g[u].push_back(v);
        }
    }
}

void DP(int u) {
    int tot = 0;
    f[u][1] = 1;
    f[u][0] = 0;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        DP(v);
        f[u][1] += min(f[v][0], f[v][1]);
        f[u][0] += f[v][1];
    }
}

int main() {
    Read();
    memset(f, 0x3f, sizeof(f));
    DP(0);
    
    printf("%d\n", min(f[0][0], f[0][1]));

    return 0;
}