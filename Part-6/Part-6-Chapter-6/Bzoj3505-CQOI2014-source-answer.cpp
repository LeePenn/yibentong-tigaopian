#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

LL C(int n) {
    return (LL)n * (n - 1) * (n - 2) / 6;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    n ++, m ++ ;

    LL res = C(n * m) - (LL)n * C(m) - (LL)m * C(n); // 全集减去水平共线和垂直共线

    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            res -= 2ll * (gcd(i, j) - 1) * (n - i) * (m - j); // 减去斜着共线

    cout << res << endl;
    return 0;
}