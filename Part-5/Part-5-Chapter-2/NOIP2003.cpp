#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100 + 2;
int n;
LL p[N];
LL f[N][N];
int path[N][N];
int lc[N], rc[N];

void Read() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &p[i]);
    }
}

LL DP(int l, int r) {
    if (l > r) return 1;
    if (f[l][r] > 0) return f[l][r];
    
    if (l == r) {
        path[l][r] = l;
        return p[l];
    }
    
    for (int i = l; i <= r; ++i) {
        LL l1 = (l <= i - 1) ? DP(l, i - 1) : 1;
        LL r1 = (r >= i + 1) ? DP(i + 1, r) : 1;
        
        if (f[l][r] < l1 * r1 + p[i]) {
            f[l][r] = l1 * r1 + p[i];
            path[l][r] = i;
        }
    }
    
    return f[l][r];
}

void Print(int l, int r) {
    if (l > r) return;
    printf("%d ", path[l][r]);
    
    if (l == r) return;
    Print(l, path[l][r] - 1);
    Print(path[l][r] + 1, r);
}

int main() {
    Read();
    
    DP(1, n);
    printf("%lld\n", f[1][n]);
    Print(1, n);
    
    return 0;
}