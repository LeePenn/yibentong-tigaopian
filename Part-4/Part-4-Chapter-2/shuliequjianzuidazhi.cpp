#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOGN = 20;
int n, m;
int a[N], Log[N];
int f[N][LOGN + 5];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    Log[0] = -1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
        Log[i] = Log[i >> 1] + 1;
    }
    
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int s = Log[r - l + 1];
        printf("%d\n", max(f[l][s], f[r - (1 << s) + 1][s]));
    }
    
    return 0;
}