#include <bits/stdc++.h>
using namespace std;
long long x[10000005], p[10000005], f[10000005];
long long n, cb[10000005], zj[10000005], a, b, c, s[10000005];
double calc(int j, int j2) {
    return 1.0 * (a * s[j] * s[j] - b * s[j] - a * s[j2] * s[j2] + b * s[j2] + f[j] - f[j2]) / (s[j] - s[j2]);
}
int q[10000005];
int main() {
    scanf("%lld", &n);
    scanf("%lld%lld%lld", &a, &b, &c);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &q[i]);
        s[i] = s[i - 1] + q[i];
    }

    int he = 0, tl = 0;

    for (int i = 1; i <= n; i++) {
        while (he < tl && calc(q[he], q[he + 1]) > 2 * a * s[i])
            he++;

        f[i] = f[q[he]] + a * (s[i] - s[q[he]]) * (s[i] - s[q[he]]) + b * (s[i] - s[q[he]]) + c;

        while (he < tl && calc(q[tl - 1], q[tl]) < calc(q[tl - 1], i))
            tl--;

        q[++tl] = i;
    }

    cout << f[n] << endl;
    return 0;
}