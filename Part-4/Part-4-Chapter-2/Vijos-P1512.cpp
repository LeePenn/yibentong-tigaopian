#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOGN = 20;

int n, m;
int a[N], st[N][LOGN + 5], Log[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    Log[0] = -1;
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
        Log[i] = Log[i >> 1] + 1;
    }
    
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }   
    
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int s = Log[r - l + 1];
        printf("%d\n", max(st[l][s], st[r - (1 << s) + 1][s]));
    }

    return 0;
}