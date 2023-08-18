#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOGN = 20;

int n, m;
int a[N], stMax[N][LOGN + 5], stMin[N][LOGN + 5], Log[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    Log[0] = -1;
    for (int i = 1; i <= n; i++) {
        stMax[i][0] = a[i];
        stMin[i][0] = a[i];
        Log[i] = Log[i >> 1] + 1;
    }
    
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            stMax[i][j] = max(stMax[i][j - 1], stMax[i + (1 << (j - 1))][j - 1]);
            stMin[i][j] = min(stMin[i][j - 1], stMin[i + (1 << (j - 1))][j - 1]);
        }
    }   
    
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int s = Log[r - l + 1];
        int Max = max(stMax[l][s], stMax[r - (1 << s) + 1][s]);
        int Min = min(stMin[l][s], stMin[r - (1 << s) + 1][s]);
        printf("%d\n", Max - Min);
    }

    return 0;
}