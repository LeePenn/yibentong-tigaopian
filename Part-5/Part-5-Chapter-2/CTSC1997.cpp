#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 5;
int n, m;
int a[N];
vector<int> son[N];
int f[N][N];

void Read() {
    scanf("%d%d", &m, &n);
    int x, y;
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &x, &y);
        son[x].push_back(i);
        a[i] = y;
    }
}

void DP(int u) {
    f[u][0] = 0;
    for (int i = 0; i < son[u].size(); ++i) {
        int v = son[u][i];
        DP(v);
        for (int j = n; j >= 0; --j) {
            for (int k = j; k >= 0; --k) {
                f[u][j] = max(f[u][j], f[v][k] + f[u][j - k]);
            }
        }
    }
    
    if (u != 0) {
        for (int i = n; i > 0; --i) {
            f[u][i] = f[u][i - 1] + a[u];
        }
    }

}

int main() {
    Read();
    memset(f, 0xcf, sizeof(f));
    DP(0);
    
    printf("%d\n", f[0][n]);

    return 0;
}