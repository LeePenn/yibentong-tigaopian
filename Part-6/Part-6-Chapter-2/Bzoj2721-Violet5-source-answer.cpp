#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10000010, MOD = 1e9 + 7;
ll n, cnt, p[N], is_p[N], a[N];
ll ans = 1;
inline ll read() {
    ll x = 0, f = 1;
    char c = getchar();

    while (!isdigit(c)) {
        if (c == '-')
            f = -1;

        c = getchar();
    }

    while (isdigit(c))
        x = x * 10 + c - 48, c = getchar();

    return x * f;
}
inline void xxs(ll n) {
    is_p[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!is_p[i])
            p[++cnt] = i;

        for (int j = 1; j <= cnt && p[j]*i <= n; j++) {
            is_p[i * p[j]] = 1;

            if (!(i % p[j]))
                continue;
        }
    }
}
int main() {
    n = read();
    xxs(n);

    for (int i = 1; i <= cnt; i++) {
        int k = p[i];

        for (ll j = k; j <= n; j *= k)
            a[i] += n / j;

        a[i] %= MOD;
    }

    for (int i = 1; i <= cnt; i++)
        ans = ans * (a[i] << 1 | 1) % MOD;

    printf("%lld", ans);
    return 0;
}