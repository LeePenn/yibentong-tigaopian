#include <bits/stdc++.h>
using namespace std;
const long long N = 3e6 + 1;
long long n, P, ans = 1;
long long cnt, a[N], p[N];
long long s, m;
long long qpow(long long a, long long b) {
    long long base = 1;

    while (b) {
        if (b & 1) {
            base = base * a % P;
        }

        a = a * a % P;
        b >>= 1;
    }

    return base;
}
void ex_lucas(long long k, long long f) {
    while (m > 0) {
        m = m / p[k];
        s += m * f;
    }
}
int main() {
    cin >> n >> P;

    for (long long i = 2; i <= n * 2; i++) {
        if (!a[i])
            p[++cnt] = i;

        for (long long j = 1; j <= cnt && p[j]*i <= n * 2; ++j) {
            a[p[j]*i] = 1;

            if (i % p[j] == 0) {
                break;
            }
        }
    }

    for (long long i = 1; i <= cnt; ++i) {
        s = 0, m = n * 2;
        ex_lucas(i, 1);
        m = n;
        ex_lucas(i, -1);
        m = n + 1;
        ex_lucas(i, -1);
        ans = ans * qpow(p[i], s) % P;
    }

    cout << ans;
    return 0;
}