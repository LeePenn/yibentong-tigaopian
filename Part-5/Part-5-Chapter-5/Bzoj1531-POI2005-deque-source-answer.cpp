#include <bits/stdc++.h>
using namespace std;
const int N = 210;
const int M = 2e4 + 10;
int n, m;
int a[N], c[N];
int q[M], l, r;
int f[M];
int val[M];
int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);

    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);

    scanf("%d", &m);
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < a[i]; j++) {
            l = 1, r = 0;

            for (int k = 0; k * a[i] + j <= m; k++) {
                val[k * a[i] + j] = f[k * a[i] + j] - k;

                while (l <= r && k - q[l] > c[i])
                    l++;

                while (l <= r && val[q[r]*a[i] + j] >= val[k * a[i] + j])
                    r--;

                q[++r] = k;
                f[k * a[i] + j] = val[q[l] * a[i] + j] + k;
            }
        }
    }

    printf("%d\n", f[m]);
}