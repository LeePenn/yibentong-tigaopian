#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2400, p = 2333;

LL T;
int c[N][N], f[N][N];

inline LL read() {
    LL r = 0, f = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }

    return r * f;
}

int lucas(LL n, LL m) {
    if (m == 0)
        return 1;

    if (n < m)
        return 0;

    if (n < p && m < p)
        return c[n][m];

    return lucas(n % p, m % p) * lucas(n / p, m / p) % p;
}

//f（n mod p，p−1）× f(n mod p,k/p−1)+C(k/p,n/p) × f(n mod p,k mod p)
int solve(LL n, LL k) {
    if (k < 0)
        return 0;

    if (n == 0 || k == 0)
        return 1;

    if (n < p && k < p)
        return f[n][k];

    return (f[n % p][p - 1] * solve(n / p, k / p - 1) % p + lucas(n / p, k / p) * f[n % p][k % p] % p) % p;
}

inline void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            if (!j)
                c[i][j] = 1;
            else
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
        }

    for (int i = 0; i < N; i++)
        f[i][0] = 1;

    for (int i = 0; i < N; i++)//组合数的前缀和
        for (int j = 1; j < N; j++) {
            f[i][j] = (f[i][j - 1] + c[i][j]) % p;
        }
}

int main() {
    init();

    T = read();

    while (T--) {
        LL n = read(), k = read();
        printf("%d\n", solve(n, k));
    }

    return 0;
}

/*https://www.cnblogs.com/genshy/p/13456251.html*/