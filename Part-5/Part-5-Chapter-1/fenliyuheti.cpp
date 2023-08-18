#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 300 + 4;
LL n, a[N], f[N][N], path[N][N];

void Read() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 0;
    }
}

void DP() {
    for (int t = 2; t <= n; ++t) {
        for (int i = 1; i + t - 1 <= n; ++i) {
            int j = i + t - 1;
            f[i][j] = 0;
            for (int k = i; k < j; ++k) {
                if (f[i][j] < f[i][k] + f[k + 1][j] + (a[i] + a[j]) * a[k]) {
                    f[i][j] = f[i][k] + f[k + 1][j] + (a[i] + a[j]) * a[k];
                    path[i][j] = k;
                }
            }
        }
    }
}

void Print() {
    queue<pair<int, int> > q;
    q.push(make_pair(1, n));
    pair<int, int> cur;
    while (!q.empty()) {
        cur = q.front(); q.pop();
        int i = cur.first, j = cur.second;
        printf("%lld ", path[i][j]);
        if (path[i][j] > i) q.push(make_pair(i, path[i][j]));
        if (path[i][j] + 1 < j) q.push(make_pair(path[i][j] + 1, j));
    }
}

int main() {
    Read();
    
    DP();
    
    printf("%lld\n", f[1][n]);
    
    Print();
    return 0;
}
