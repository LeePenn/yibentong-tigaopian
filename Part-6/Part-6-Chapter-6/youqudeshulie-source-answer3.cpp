#include <iostream>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 9;
int pri[N], cnt;
bool st[N];
int n, mod;
int get(int x, int p) {
    int ans = 0;

    while (x != 0)
        ans += x / p, x /= p;

    return ans;
}
ll quick_pow(ll x, int y) {
    ll ans = 1;

    while (y != 0) {
        if (y & 1)
            ans = ans * x % mod;

        x = x * x % mod;
        y /= 2;
    }

    return ans;
}
ll C(int a, int b) { //求组合数
    int ans = 1;

    for (int i = 1; i <= cnt; i++) {
        int s = get(a, pri[i]) - get(b, pri[i]) - get(a - b, pri[i]);
        ans = ans * quick_pow(pri[i], s) % mod;
    }

    return ans;
}
int main() {
    scanf("%d%d", &n, &mod);

    for (int i = 2; i <= 2 * n; i++) {
        if (st[i] == false)
            pri[++cnt] = i;

        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > 2 * n)
                break;

            st[i * pri[j]] = true;

            if (i % pri[j] == 0)
                break;
        }
    }

    printf("%lld", (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod);
    return 0;
}