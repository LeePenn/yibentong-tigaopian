#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL n, k, p = 5000011;

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
        if (b & 1) {
            ret = ret * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ret;
}

LL calc(LL n, LL m) {
    if (!m) return 1;
    LL a = 1, b = 1;
    for (int i = 1; i <= m; ++i) {
        a = a * (n - m + i) % p;
        b = b * i % p;
    }
    
    return (a * ksm(b, p - 2)) % p;
}

/*
    如果有x头牡牛，就一定会有(x - 1) * k头牝牛，也就是说牡牛只能在剩下的n - (x - 1) * k个位置上选
    所以方案数是C(n - (x - 1) * k, x)，当x > n - (x - 1) * k时退出
*/
int main() {
    cin >> n >> k;
    LL ans = 0;
    for (LL i = 0; i <= n; ++i) {
        if (i > n - (i - 1) * k) break;
        ans = (ans + calc(n - (i - 1) * k, i)) % p;
    }
    
    cout << ans << endl;
    
    return 0;
}

