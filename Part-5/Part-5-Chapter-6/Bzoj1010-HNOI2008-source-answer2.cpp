#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 5;
int n, l, c[N], f[N], pre[N], q[N], head = 1, tail = 1;
int calc(int i, int j) {
    return f[i] + (c[j] - c[i] - l) * (c[j] - c[i] - l);
}
int get(int i, int j) {
    int l = j, r = n, res = n + 1;

    while (l <= r) {
        int mid = l + r >> 1;

        if (calc(i, mid) >= calc(j, mid)) {
            res = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }

    return res;
}
signed main() {
    scanf("%lld%lld", &n, &l);
    l++;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
        c[i] = c[i] + 1 + c[i - 1];
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;

    for (int i = 1; i <= n; i++) {
        while (head < tail && calc(q[head], i) >= calc(q[head + 1], i))
            head++;

        f[i] = calc(q[head], i);

        while (head < tail && get(q[tail - 1], q[tail]) >= get(q[tail], i))
            tail--;

        q[++tail] = i;
    }

    printf("%lld", f[n]);
    return 0;
}