#include <cstdio>
#define LL long long

const int N = 1e5 + 10;
LL P[N], C[N], X[N], w[6], sum;
int cnt;

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

LL qmi(LL a, LL b, LL p) {
    LL res = 1;

    while (b) {
        if (b & 1)
            res = res * a % p;

        a = a * a % p;
        b >>= 1;
    }

    return res;
}

LL inverse(LL a, LL b) {
    LL x, y;
    exgcd(a, b, x, y);
    return (x % b + b) % b;
}

LL fac(LL n, LL q, LL p) {
    if (!n)
        return 1;

    LL res = 1;

    for (int i = 2; i <= p; i ++)
        if (i % q)
            res = res * i % p;

    res = qmi(res, n / p, p);

    for (int i = 2; i <= n % p; i ++)
        if (i % q)
            res = res * i % p;

    return res * fac(n / q, q, p) % p;
}

LL multilucas(LL a, LL b, LL x, LL p) {
    LL tot = 0;

    for (LL i = a; i ; i /= x)
        tot += i / x;

    for (LL i = b; i ; i /= x)
        tot -= i / x;

    for (LL i = a - b; i ; i /= x)
        tot -= i / x;

    return qmi(x, tot, p) * fac(a, x, p) % p * inverse(fac(b, x, p), p) % p * inverse(fac(a - b, x, p), p) % p;
}

LL crt(LL a, LL b) {
    for (int i = 1; i <= cnt; i ++)
        C[i] = multilucas(a, b, X[i], P[i]);

    LL res = C[1], M = P[1], x, y, d, p;

    for (int i = 2; i <= cnt; i ++) {
        d = exgcd(M, P[i], x, y);
        p = P[i] / d;

        if ((C[i] - res) % d)
            return -1;

        x = (C[i] - res) / d * x % p;
        x = (x + p) % p;
        res += x * M;
        M *= p;
        res = (res % M + M) % M;
    }

    return res;
}

int main() {
    int p, n, m, tp;
    scanf("%d %d %d", &p, &n, &m);
    tp = p;

    for (int i = 1; i <= m; i ++) {
        scanf("%lld", &w[i]);
        sum += w[i];
    }

    if (sum > n)
        return puts("Impossible"), 0;

    for (int i = 2; i <= p / i; i ++)
        if (p % i == 0) {
            P[++ cnt] = 1, X[cnt] = i;

            while (p % i == 0)
                P[cnt] *= i, p /= i;
        }

    if (p > 1)
        P[++ cnt] = p, X[cnt] = p;

    LL ans = 1;

    for (int i = 1; i <= m; i ++) {
        ans = ans * crt(n, w[i]) % tp;
        n -= w[i];
    }

    printf("%lld", ans);
    return 0;
}