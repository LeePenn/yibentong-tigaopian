#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 4;
int a[N][N], f[N][N];
int l[N], r[N];
int n, m;
int p[N];

void Read() {
    scanf("%d%d", &n, &m);
    m++;
    memset(a, -1, sizeof(a));
    int u, v, x;
    for (int i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &x);
        a[u][v] = a[v][u] = x;
    }
}

void Build(int u) {
    for (int i = 1; i <= n; ++i) {
        if (a[u][i] >= 0) {
            l[u] = i;
            p[i] = a[u][i];
            a[u][i] = a[i][u] = -1;
            Build(i);
            break;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        if (a[u][i] >= 0) {
            r[u] = i;
            p[i] = a[u][i];
            a[u][i] = a[i][u] = -1;
            Build(i);
            break;
        }
    }
}

int DP(int u, int q) {
    if (q == 0) return 0;
    if (l[u] == 0 && r[u] == 0) return p[u];
    if (f[u][q] > 0) return f[u][q];
    
    for (int k = 0; k <= q - 1; ++k) {
        f[u][q] = max(f[u][q], DP(l[u], k) + DP(r[u], q - k - 1) + p[u]);
    }
    
    return f[u][q];
    
}

int main() {
    Read();
    Build(1);
    printf("%d\n", DP(1, m));
    
    return 0;
}