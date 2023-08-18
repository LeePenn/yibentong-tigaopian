#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 2, INF = 0x3f3f3f3f;
int n, a[N << 1], sum[N << 1];
int Fmin[N << 1][N << 1], Fmax[N << 1][N << 1];

void Read() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[n + i] = a[i];
    }
    for (int i = 1; i <= (n << 1); i++) {
        sum[i] = sum[i - 1] + a[i];
        Fmin[i][i] = 0;
        Fmax[i][i] = 0;
    }
}

void DP() {
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= 2 * n - L + 1; i++) {
            int j = i + L - 1;
            Fmin[i][j] = INF, Fmax[i][j] = 0;
            for (int k = i; k < j; k++) {
                Fmin[i][j] = min(Fmin[i][j], Fmin[i][k] + Fmin[k + 1][j] + sum[j] - sum[i - 1]);
                Fmax[i][j] = max(Fmax[i][j], Fmax[i][k] + Fmax[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }
    
    int ansmin = INF, ansmax = 0;
    for (int i = 1; i <= n; i++) {
        ansmin = min(ansmin, Fmin[i][i + n - 1]);
        ansmax = max(ansmax, Fmax[i][i + n - 1]);
    }
    printf("%d\n%d\n", ansmin, ansmax);
}

int main() {
    Read();
    DP();

    return 0;
}