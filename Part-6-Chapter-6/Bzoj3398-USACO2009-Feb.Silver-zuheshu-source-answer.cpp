#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <set>
using namespace std;
#define Max 0x7fffffff
#define  LL long long
#define int long long
int mod = 5000011;
#define N 200006
using namespace std;
LL qpow(int res, int p, int q) {
    LL ans = 1;

    while (p) {
        if (p & 1)
            ans = res * ans % q;

        res = res * res % q;
        p = p >> 1;
    }

    return ans;
}
LL cal(int n, int m, int p) {
    LL ans = 1, res = 1;

    for (int i = 1; i <= m; i++) {
        ans = (ans * n--) % p;
        res = res * i % p;
    }

    return ans * qpow(res, p - 2, p) % p;
}
signed main() {
    LL ans = 0;
    int n, k;
    cin >> n >> k;
    int maxn = n / (k + 1);

    if (maxn * (k + 1) != n)
        maxn++;

    for (int i = 1; i <= maxn; i++)
        ans = (ans % mod + cal(n - k * i + k, i, mod) % mod) % mod;

    cout << (ans + 1) % mod;
    return 0;

}