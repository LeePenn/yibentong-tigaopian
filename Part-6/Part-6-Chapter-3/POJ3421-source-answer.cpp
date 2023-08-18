#include <bits/stdc++.h>
using namespace std;
long long n, prime[100010], v[100010], cnt, t[100010], b[1010], tot;
long long ans;
void pri() {
    for (int i = 2; i <= 100000; ++i) {
        if (v[i] == 0) {
            v[i] = i;
            prime[++cnt] = i;
        }

        for (int j = 1; j <= cnt; ++j) {
            if (prime[j] > v[i] || prime[j]*i > 100000)
                break;

            v[prime[j]*i] = prime[j];
        }
    }
}
void fj(int x) {
    long long s = 0, tot = 0, ans = 1;
    memset(t, 0, sizeof(t));

    for (int i = 1; i <= cnt; ++i) {
        if (x % prime[i] == 0)
            b[++tot] = prime[i];

        while (1) {
            if (x % prime[i] != 0 || x == 1)
                break;

            x /= prime[i];
            ++t[prime[i]];
        }

        s += t[prime[i]];

        if (prime[i] > x)
            break;
    }//求质因子个数

    if (x > 1)
        s++;

    cout << s << ' ';

    for (int i = 1; i <= s; ++i)
        ans *= i;

    for (int i = 1; i <= tot; ++i) {
        long long c = 1;

        for (int j = 1; j <= t[b[i]]; ++j)
            c *= j;

        ans /= c;
    }/*用排列、组合方法求组数

                                    A(n1+n2~~+nm)/(n1+n2~~+nm)
    p1^n1 * p2^n2 ~~ * pm^nm ==>------------------------------------
                                 A(n1)/(n1)*A(n2)/(n2)~~*A(nm)/(nm)
    */
    cout << ans << '\n';
}
int main() {
    pri();

    while (cin >> n)
        fj(n);
}