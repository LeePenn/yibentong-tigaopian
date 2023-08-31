#include <bits/stdc++.h>
using namespace std;
int a[100005], b[100005], n, x, len;
int main() {
    scanf("%d", &n);
    a[1] = 1;
    len = 1;

    for (int i = n + 2; i <= 2 * n; ++i) {
        for (int j = 1; j <= len; ++j) {
            a[j] = a[j] * i + x;
            x = a[j] / 10;
            a[j] %= 10;
        }

        while (x) {
            a[++len] = x % 10;
            x /= 10;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = len; j >= 1; --j) {
            a[j] = a[j] + a[j + 1] * 10;
            b[j] = a[j] / i;
            a[j] %= i;
        }

        while (!b[len])
            a[len--] = 0;

        for (int j = 1; j <= len; ++j)
            a[j] = b[j];
    }

    for (int i = len; i >= 1; --i)
        printf("%d", a[i]);

    return 0;
}