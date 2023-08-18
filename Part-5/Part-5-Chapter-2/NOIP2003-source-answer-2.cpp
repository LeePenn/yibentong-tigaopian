#include <bits/stdc++.h>
using namespace std;
long long n, i, a[35], g[105][105], f[105][105], j, step, k;
void print(int i, int j) {
    if (g[i][j] == 0)
        return;

    cout << g[i][j] << " ";

    if (i < g[i][j])
        print(i, g[i][j] - 1);

    if (g[i][j] < j)
        print(g[i][j] + 1, j);
}
int main() {
    cin >> n;

    for (i = 1; i <= n; i++) {
        cin >> f[i][i];
        f[i][i - 1] = 1;
        g[i][i] = i;
    }

    f[n + 1][n] = 1;

    for (i = n - 1; i >= 1; i--)
        for (j = i + 1; j <= n; j++)
            for (k = i; k <= j; k++)
                if (f[i][j] < f[i][k - 1]*f[k + 1][j] + f[k][k]) {
                    f[i][j] = f[i][k - 1] * f[k + 1][j] + f[k][k];
                    g[i][j] = k;
                }

    cout << f[1][n] << endl;
    print(1, n);
    return 0;
}