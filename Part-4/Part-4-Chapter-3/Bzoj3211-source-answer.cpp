#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1000005;
int n, m;
int a[maxn], mx[maxn << 2], sum[maxn << 2];

inline void up(int k) {
    mx[k] = max(mx[k << 1], mx[k << 1 | 1]);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

inline void build(int k, int l, int r) {
    if (l == r) {
        sum[k] = mx[k] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    up(k);
}

void change(int k, int l, int r, int x, int y) {
    if (l == r && l >= x && r <= y) {
        sum[k] = mx[k] = sqrt(sum[k]);
        return ;
    }

    int mid = (l + r) >> 1;

    if (x <= mid && mx[k << 1] > 1)
        change(k << 1, l, mid, x, y);

    if (y > mid && mx[k << 1 | 1] > 1)
        change(k << 1 | 1, mid + 1, r, x, y);

    up(k);
}
int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y)
        return sum[k];

    int ans = 0, mid = (l + r) >> 1;

    if (x <= mid)
        ans += query(k << 1, l, mid, x, y);

    if (y > mid)
        ans += query(k << 1 | 1, mid + 1, r, x, y);

    return ans;
}
signed main() {
    scanf("%lld", &n);

    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    build(1, 1, n);
    scanf("%lld", &m);

    while (m--) {
        int op, l, r;
        scanf("%lld%lld%lld", &op, &l, &r);

        if (l > r)
            swap(l, r);

        if (op == 1)
            printf("%lld\n", query(1, 1, n, l, r));
        else
            change(1, 1, n, l, r);
    }

    return 0;
}