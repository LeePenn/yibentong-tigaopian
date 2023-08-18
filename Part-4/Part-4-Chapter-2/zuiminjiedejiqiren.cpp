#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOGN = 20;
int n, k, Log[N];
int a[N];
int fMax[N][LOGN + 5], fMin[N][LOGN + 5];

void work() {
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            fMax[i][j] = max(fMax[i][j - 1], fMax[i + (1 << (j - 1))][j - 1]);
            fMin[i][j] = min(fMin[i][j - 1], fMin[i + (1 << (j - 1))][j - 1]);
        }
    }   
    
    for (int i = 1; i + k - 1 <= n; i++) {
        int s = Log[k];
        printf("%d ", max(fMax[i][s], fMax[i + k - 1 - (1 << s) + 1][s]));
        printf("%d\n", min(fMin[i][s], fMin[i + k - 1 - (1 << s) + 1][s]));
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    Log[0] = -1;
    for (int i = 1; i <= n; i++) {
        fMax[i][0] = a[i];
        fMin[i][0] = a[i];
        Log[i] = Log[i >> 1] + 1;
    }
    
    work();

    return 0;
}