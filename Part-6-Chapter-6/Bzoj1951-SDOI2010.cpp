#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, g;
LL a[4] = {2, 3, 4679, 35617};
LL p[36000], b[4], ans, mod = 999911658;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ksm(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

void exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    LL t = x;
    x = y;
    y = t - a / b * y;
}

LL inv(LL a, LL p) {
    LL x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

LL Lucas(LL x, LL mod) {
    LL ans = 1, y, a, b;
    for (y = n; x; x /= mod, y /= mod) {
        a = x % mod, b = y % mod;
        ans = (LL)ans * p[b] % mod * inv(p[a], mod) % mod * inv(b < a ? 0 : p[b - a], mod) % mod;
    }
    return ans;
}

int main() {
    cin >> n >> g;
    g %= mod + 1;
    if (!g) {
        cout << 0 << endl;
        return 0;
    }
    p[0] = 1;
    for (int i = 1; i <= a[3]; ++i) p[i] = p[i - 1] * i % mod;
    
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            for (int j = 0; j < 4; ++j) b[j] = (b[j] + Lucas(i, a[j])) % a[j];
            if (i * i != n) {
                for (int j = 0; j < 4; ++j) b[j] = (b[j] + Lucas(n / i, a[j])) % a[j];
            }
        }
    }
    
    LL x, y;
    for (int i = 0; i < 4; ++i) {
        exgcd(mod / a[i], a[i], x, y);
        ans = (ans + x * (mod / a[i]) % mod * b[i]) % mod;
    }
    
    ans = (ans % mod + mod) % mod;
    mod++;
    ans = ksm(g, ans);
    cout << ans << endl;
    
    return 0;
}

