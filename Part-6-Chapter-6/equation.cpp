#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL k, x, n, p = 1000;
LL a[1000], b[1000];

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
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

LL Gcd(LL a, LL b) {
    if (!b) return a;
    return Gcd(b, a % b);
}

void Print(LL a[]) {
    for (int i = a[0]; i >= 1; --i) {
        cout << a[i];
    }
    cout << endl;
}

void C(LL n, LL m) {
    if (n < m) {
        cout << 0 << endl;
        return;
    }
    
    for (int i = 1; i <= m; ++i) {
        a[i] = n - m + i;
        b[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (b[i] == 1) continue;
        for (int j = m; j >= 1; --j) {
            LL x = Gcd(b[i], a[j]);
            a[j] /= x;
            b[i] /= x;
            if (b[i] == 1) break;
        }
    }
    memset(b, 0, sizeof(b));
    b[0] = b[1] = 1;
    LL g = 0;
    for (int i = 1; i <= m; ++i) {
        g = 0;
        for (int j = 1; j <= b[0]; ++j) {
            b[j] = b[j] * a[i] + g;
            g = b[j] / 10;
            b[j] %= 10;
        }
        while (g > 0) {
            b[0]++;
            b[b[0]] = g % 10;
            g /= 10;
        }
    }
    
    Print(b);
    
}

int main() {
    cin >> k >> x;
    n = ksm(x, x);
    // C(10, 3);
    // printf("$$$$ %lld %lld\n", n, k - 1);
    C(n - 1, k - 1);
    
    return 0;
}

