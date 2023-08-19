#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
    char c = getchar();
    int x = 0, fh = 0;

    while (c < '0' || c > '9') {
        fh |= c == '-';
        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }

    return fh ? -x : x;
}
int a[240] = {0, 23, 28, 33}, b[240], ans, d, t;
void exgcd(int a, int b, int &w, int &x, int &y) {
    int t;

    if (b == 0) {
        w = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b, w, x, y);
        t = x;
        x = y;
        y = t - (a / b) * y;
    }
}
void intchina() {
    int m = 1, x, y, w;
    ans = 0;
    m = 23 * 28 * 33;

    for (int i = 1; i <= 3; i++) {
        int mi = m / a[i];
        exgcd(mi, a[i], w, x, y);
        ans = ((ans + mi * x * b[i]) % m + m) % m;

        while (ans <= d)
            ans += m;
    }

    printf("Case %lld: the next triple peak occurs in %lld days.\n", t, ans - d);
}
signed main() {
    while (cin >> b[1] >> b[2] >> b[3] >> d) {
        t++;

        if (b[1] == -1)
            break;

        intchina();
        memset(b, 0, sizeof b);
    }

    return 0;
}